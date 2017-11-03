using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security;
using System.Text;
using UnityEditor;
using UnityEngine;
using System.Security.Cryptography;
public enum ResourceSource
{
    Local,
    Net,
}

public enum PanelType
{
    BaseInfo,
    Program,
}

public class BuildStudio : EditorWindow
{
    public const string StreamingABFloder = "Assets/StreamingAssets/" + GameConfig.BuildOption.abFloder;

    string __KeyVersion = "__CurrentVersion";
    string __KeyPlatform = "__CurrentTarget";
    string __KeyToolPanelOpen = "__ToolPanelOpen";
    string __KeyResourceSource = "__ResourceSource";

    static GameVersion mCurrentVersion = new GameVersion();

    static PanelType mPanelType = PanelType.BaseInfo;

    static ResourceSource mResourceSource = ResourceSource.Local;
    static bool mToolPanelOpen = true;


    static List<string> mCurrentAssetBundleNames = new List<string>();
    static bool mBuilding = false;


    [MenuItem("FF/BuildTool/Open")]
    public static void ShowBuildStudio()
    {
        var studio = EditorWindow.GetWindow(typeof(BuildStudio)) as BuildStudio;
        studio.Show();
    }

    string[] sPanelText = new string[]
    {
        "基本信息",
        "程序操作",
    };

    void OnGUI()
    {
        EditorGUILayout.ObjectField(this, typeof(BuildStudio), false, GUILayout.Width(100f));
        mPanelType = (PanelType)GUILayout.Toolbar((int)mPanelType, sPanelText);

        GUILayout.Space(10);

        switch (mPanelType)
        {
            case PanelType.BaseInfo:
            {
                DrawBaseInfo();
                DrawBuildPlayer();
                break;
            }
            case PanelType.Program:
            {
                DrawProgramPanel();
            }
            break;
        }
    }

    public  void DrawMiddleOperation()
    {
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("1|生成依赖"))
        {
            ABExporter.GenerateDepencices();
        }
        if (GUILayout.Button("2生成AB名字"))
        {
            ABExporter.ExportABNames();
        }
        if (GUILayout.Button("3|设置资源AB名字"))
        {
            ABExporter.SetAllABNames();
        }
        if (GUILayout.Button("4|导出版本信息"))
        {
            ExportABVersion();
        }
        if (GUILayout.Button("5|清除无效文件"))
        {
            ABExporter.ClearGarbageAB();
        }
        if (GUILayout.Button("6|检错"))
        {
            ABExporter.CheckError();
        }
        if (GUILayout.Button("7|生成AB"))
        {
            ABExporter.BuildAB();
        }
        GUILayout.EndHorizontal();
    }
    void DrawProgramPanel()
    {
        if (GUILayout.Button("Tool"))
        {
            mToolPanelOpen = !mToolPanelOpen;
            PlayerPrefs.SetInt(__KeyToolPanelOpen, mToolPanelOpen ? 1 : 0);
        }
        if (mToolPanelOpen)
            DrawToolPanel();
        GUILayout.Space(10);
        DrawMiddleOperation();
        ABExporter.OnGUI();
    }

    static string[] sDefineTypes = new string[]
    {
        "OnePerFile",
        "OnePerFloder",
        "OnePerName",
    };


    void DrawQuickFloder()
    {
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("打开资源目录"))
        {
            var path = Path.Combine(Path.GetDirectoryName(Application.dataPath), GameConfig.BuildOption.localABFloder).Replace("/", "\\");
            Basic.Assist.OpenFloder(path);
        }
        if (GUILayout.Button("打开SD目录"))
        {
            var path = Application.persistentDataPath.Replace("/", "\\");
            Basic.Assist.OpenFloder(path);
        }
        if (GUILayout.Button("打开APK目录"))
        {
            var path = Basic.Assist.CombineWithBSlash(Path.GetDirectoryName(Application.dataPath), "output");
            Basic.Assist.OpenFloder(path);
        }
        GUILayout.EndHorizontal();
    }

    string mDefinations = string.Empty;
    static string ABMacro = "LOAD_FROM_AB";
    static bool mIsGoogleAndroidProject = false;

    void PushDefinations()
    {
        BuildTargetGroup group = ABExporter.buildTarget == BuildTarget.Android ? BuildTargetGroup.Android : BuildTargetGroup.iOS;
        mDefinations = PlayerSettings.GetScriptingDefineSymbolsForGroup(group);
        if(mDefinations.IndexOf(ABMacro) == -1)
            PlayerSettings.SetScriptingDefineSymbolsForGroup(group, mDefinations + ";" + ABMacro);
        string content = PlayerSettings.GetScriptingDefineSymbolsForGroup(group);
        AssetDatabase.Refresh();
    }

    void PopDefinations()
    {
        BuildTargetGroup group = ABExporter.buildTarget == BuildTarget.Android ? BuildTargetGroup.Android : BuildTargetGroup.iOS;
        mDefinations = mDefinations.Replace(ABMacro + ";", "");
        mDefinations = mDefinations.Replace(ABMacro, "");
        PlayerSettings.SetScriptingDefineSymbolsForGroup(group, mDefinations);
        AssetDatabase.Refresh();
    }

    void DrawBuildPlayer()
    {
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("重新生成资源"))
        {
            ClearAssetBundlesNames();
            Basic.Assist.Watch(ABExporter.OneKeyExportAB);
            ExportABVersion();
        }
        if (GUILayout.Button("增量生成资源"))
        {
            Basic.Assist.Watch(ABExporter.OneKeyExportAB);
            ExportABVersion();
        }
        if (GUILayout.Button("一键生成APP"))
        {
            Basic.Assist.BeginWatch("AllTime");
            Basic.Assist.Watch(ABExporter.OneKeyExportAB);
            ExportABVersion();
            Basic.Assist.Watch(CopyToStreamingAssets);
            PushDefinations();
            Basic.Assist.Watch(DoBuildPlayer);
            PopDefinations();
            Basic.Assist.EndWatch();
        }
        mIsGoogleAndroidProject = EditorGUILayout.Toggle("生成谷歌工程", mIsGoogleAndroidProject);
        GUILayout.EndHorizontal();
    }
    void BuildPlayer()
    {

        string[] scenenames = new string[]
        {
            Basic.Assist.CombineWithSlash(Application.dataPath, "Scenes/Startup.unity"),
        };

        var dir = Basic.Assist.CombineWithSlash(Path.GetDirectoryName(Application.dataPath), "output");

        if (!string.IsNullOrEmpty(dir))
        {
            string path = Basic.Assist.CombineWithSlash(dir, ABExporter.GetPlatformString());

            Basic.Assist.CreateDirectoryIfNotExist(path);

            BuildOptions options = BuildOptions.AllowDebugging | BuildOptions.ConnectWithProfiler;

            if (ABExporter.IsAndroid())
            {
                if (!mIsGoogleAndroidProject)
                {
                    path = Path.Combine(path, PlayerSettings.productName + ".apk");
                    if (ABExporter.buildTarget == BuildTarget.Android)
                        options = BuildOptions.Development | BuildOptions.AllowDebugging | BuildOptions.ConnectWithProfiler;
                }
                else
                {
                    options = BuildOptions.AcceptExternalModificationsToPlayer | BuildOptions.AllowDebugging | BuildOptions.ConnectWithProfiler;
                }
            }

            UnityEngine.Debug.LogWarning("Out Path:" + path);

            BuildPipeline.BuildPlayer(scenenames, path, ABExporter.buildTarget, options);
        }
        Basic.Assist.OpenFloder(Basic.Assist.CombineWithBSlash(Path.GetDirectoryName(Application.dataPath), "output"));
    }

    void DoBuildPlayer()
    {
        PushDefinations();
        BuildPlayer();
        PopDefinations();
    }

    void DrawBaseInfo()
    {
        GUILayout.BeginHorizontal();
        GUILayout.Label("当前版本号", GUILayout.Width(120f));
        string version = EditorGUILayout.TextField(mCurrentVersion.ToString());
        if (version != mCurrentVersion.ToString())
        {
            mCurrentVersion = GameVersion.Parse(version);
            PlayerPrefs.SetString(__KeyVersion, mCurrentVersion.ToString());
        }
        if (GUILayout.Button("提升程序版本", GUILayout.Width(120f)))
        {
            mCurrentVersion.program++;
            mCurrentVersion.resource = 0;
            PlayerPrefs.SetString(__KeyVersion, mCurrentVersion.ToString());
        }
        if (GUILayout.Button("提升资源版本", GUILayout.Width(120f)))
        {
            mCurrentVersion.resource++;
            PlayerPrefs.SetString(__KeyVersion, mCurrentVersion.ToString());
        }

        GUILayout.EndHorizontal();

        GUILayout.BeginHorizontal();
        GUILayout.Label("平台", GUILayout.Width(40));
        {
            BuildTarget target = (BuildTarget)EditorGUILayout.EnumPopup(ABExporter.buildTarget);
            if (target != ABExporter.buildTarget)
            {
                ABExporter.buildTarget = target;
                PlayerPrefs.SetString(__KeyPlatform, ABExporter.buildTarget.ToString());
            }
        }
        GUILayout.EndHorizontal();
    }

    static void ExportABVersion()
    {
        mCurrentVersion.time = System.DateTime.Now.ToString();
        string srcPath = GetServerFloder() + "/" + GameConfig.BuildOption.abVersionFile;
        string dstPath = GetServerFloder() + "/" + "indexs.json";
        string src1Path = GetServerFloder() + "/" + "indexsd.json";
        bool ret = Basic.Assist.SaveJsonObject(mCurrentVersion, srcPath);
    }

    static string GetSelectFloder()
    {
        var selectpath = AssetDatabase.GetAssetPath(Selection.activeObject);
        string pathroot = Path.GetDirectoryName(Application.dataPath);
        string path = Path.Combine(pathroot, selectpath);
        return path;
    }

    void ClearOldAB()
    {
        DirectoryInfo dir = new DirectoryInfo(ABExporter.GetABFloder());
        if (dir.Exists)
            Directory.Delete(dir.FullName, true);
    }
    void ClearOldResourceInfoListFileInfo()
    {
        {
            string resourceListFile = GetIndexFileName();
            if (File.Exists(resourceListFile))
                File.Delete(resourceListFile);
        }
        {
            string resourceListFile = GetInvlidListFileName();
            if (File.Exists(resourceListFile))
                File.Delete(resourceListFile);
        }
    }

    void CopyToStreamingAssets()
    {
        string path = GetServerFloder();
        if (!Directory.Exists(Application.streamingAssetsPath))
            Directory.CreateDirectory(Application.streamingAssetsPath);
        Basic.Assist.CopyFloder(path, Application.streamingAssetsPath, true, true, true, new string[] { ".manifest" });
    }

    void ClearStreamingAssets()
    {
        Basic.Assist.DeleteFolder(Application.streamingAssetsPath);
    }

    void SetResourceFromNet()
    {
        PlayerSettings.SetScriptingDefineSymbolsForGroup(BuildTargetGroup.Android | BuildTargetGroup.iOS, "LOAD_FROM_AB");
    }
    void SetResourceFromLocal()
    {
        PlayerSettings.SetScriptingDefineSymbolsForGroup(BuildTargetGroup.Android | BuildTargetGroup.iOS, string.Empty);
    }

    void DrawToolPanel()
    {
        DrawQuickFloder();
        GUILayout.BeginHorizontal();

        //if (GUILayout.Button("压缩"))
        //{
        //    CreateIfNotExistDirectroy(GetABFloder_Compressed());
        //    SingleCompress();
        //    CopyListInfoToUncompress();
        //    ClearUnuseAB(GetABFloder_Compressed());
        //}
        if (GUILayout.Button("拷贝到流资源目录下"))
        {
            Basic.Assist.Watch(CopyToStreamingAssets);
        }
        if (GUILayout.Button("生成APK"))
        {
            Basic.Assist.Watch(DoBuildPlayer);
        }
        GUILayout.EndHorizontal();
    }
    static void ClearSDVersionInfo()
    {
        string path = Application.persistentDataPath;
        Basic.Assist.DeleteFolder(path);
    }

    static string GetServerFloder()
    {
        return Basic.Assist.CombineWithSlash(GameConfig.BuildOption.localABFloder, ABExporter. GetPlatformString());
    }
    static string GetStreamingABFloder()
    {
        return Application.streamingAssetsPath;
    }
    static string GetIndexFileName()
    {
        string path = Path.Combine(GetServerFloder(), GameConfig.BuildOption.abIndexFile);
        return path;
    }
    static string GetInvlidListFileName()
    {
        string path = Path.Combine(GetServerFloder(), "invalid_resources.json");
        return path;
    }

    static ABIndex GetAssetBundleInfoListFromFile()
    {
        string fileFullName = GetIndexFileName();
        if (File.Exists(fileFullName))
        {
            string content = File.ReadAllText(fileFullName);
            return JsonUtility.FromJson<ABIndex>(content);
        }
        return null;
    }

    void ClearAssetBundlesNames()
    {
        string[] names = AssetDatabase.GetAllAssetBundleNames();
        int count = names.Length;
        if (count == 0)
            return;
        for (int i = 0; i < count; ++i)
        {
            var name = names[i];
            //if (name.StartsWith("sgq_ab"))
            {
                AssetDatabase.RemoveAssetBundleName(name, true);
                int cur = i + 1;
                if (EditorUtility.DisplayCancelableProgressBar(string.Format("Clear OldNames({0}/{1})", cur, count), name, (float)(i + 1) / names.Length))
                {
                    EditorUtility.ClearProgressBar();
                    return;
                }
            }
        }
        EditorUtility.ClearProgressBar();
        return;
    }

    void OnFocus()
    {
        {
            string version = PlayerPrefs.GetString(__KeyVersion);
            if (!string.IsNullOrEmpty(version))
                mCurrentVersion = GameVersion.Parse(version);
        }
        {
            string target = PlayerPrefs.GetString(__KeyPlatform);
            if (!string.IsNullOrEmpty(target))
                ABExporter.buildTarget = (BuildTarget)Enum.Parse(typeof(BuildTarget), target);
        }

        {
            int toolPanelOpen = PlayerPrefs.GetInt(__KeyToolPanelOpen);
            mToolPanelOpen = toolPanelOpen > 0 ? true : false;
        }

        {
            string target = PlayerPrefs.GetString(__KeyResourceSource);
            if (!string.IsNullOrEmpty(target))
                mResourceSource = (ResourceSource)Enum.Parse(typeof(ResourceSource), target);
        }

        ABExporter.OnFocus();
    }





}