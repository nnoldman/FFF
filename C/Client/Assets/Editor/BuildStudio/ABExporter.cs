using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UnityEditor;
using UnityEngine;

public static class ABExporter
{
    static string[] resourceExtensions = new string[]
    {
        ".psd", ".jpg", ".jpeg", ".gif", ".png", ".tiff", ".tif", ".tga", ".bmp", ".dds",  ".exr", ".iff", ".pict",
        ".prefab", ".unity",
        ".fbx", ".dae", ".mb", ".ma", ".max", ".blend", ".obj", ".3ds", ".dxf",
        ".anim", ".controller", ".mask",
        ".mov", ".mpg", ".mpeg", ".mp4", ".avi", ".asf",
        ".mat", ".sbsar", ".cubemap", ".flare",
        ".shader", ".compute", ".cginc",
        ".guiskin", ".fontsettings", ".ttf", ".dfont", ".otf",
        ".wav", ".mp3", ".ogg", ".aif", ".xm", ".mod", ".it", ".s3m",
        ".txt", ".bytes", ".html", ".xml", ".json",
        ".asset", ".physicmaterial", ".unity",
    };

    static string[] mustOneABExtensions =
    {
        ".jpg", ".png", ".exr", ".dds", ".tga",
        ".ttf",
        ".unity",
        "fbx", ".obj",
    };

    static string __KeyResourceSource = "__CDNAddress";
    static string cdnAddress = string.Empty;

    public static void OnFocus()
    {
        cdnAddress = PlayerPrefs.GetString(__KeyResourceSource);
    }
    public static void SaveCDNAddr()
    {
        PlayerPrefs.SetString(__KeyResourceSource, cdnAddress);
    }

    public static HashSet<string> resourceExtensionSet
    {
        get
        {
            if (mResourceExtensionSet == null)
            {
                mResourceExtensionSet = new HashSet<string>();
                foreach (var ext in resourceExtensions)
                    mResourceExtensionSet.Add(ext);
            }
            return mResourceExtensionSet;
        }
    }
    static HashSet<string> mResourceExtensionSet;


    static ABIndex abIndex
    {
        get
        {
            if(mABIndex == null)
            {
                mABIndex = Basic.Assist.LoadJsonObject<ABIndex>(GetIndexFileWithTarget(), GameConfig.BuildOption.abIndexCompressed);
            }
            if (mABIndex == null)
            {
                mABIndex = new ABIndex();
            }
            return mABIndex;
        }
    }
    static ABIndex mABIndex;

    private const int kSpace = 20;
    private static ABDefineSet mDefineSet;
    private static BuildTarget mBuildTarget = BuildTarget.Android;

    private static Vector2 mScrollPosition = Vector2.zero;
    private static bool mShowReexport = false;

    static void DrawABDefines()
    {
        mScrollPosition = GUILayout.BeginScrollView(mScrollPosition);
        int x = 5;
        GUILayout.EndScrollView();
    }

    public static void OnGUI()
    {
        DrawDefineTools();
        //DrawABDefines();
    }

    public static void OneKeyExportAB()
    {
        ABExporter.GenerateDepencices();
        ABExporter.ExportABNames();
        ABExporter.SetAllABNames();
        ABExporter.ClearOldABNames();
        ABExporter.CheckObjectRef();
        ABExporter.ClearGarbageAB();
        ABExporter.BuildAB();
    }
    public static void DrawDefineTools()
    {
        GUILayout.BeginVertical();
        GUILayout.BeginHorizontal();
        GUILayout.Label("CDN", GUILayout.Width(80));
        string ret = EditorGUILayout.TextField(cdnAddress);
        if(ret.Length != cdnAddress.Length)
        {
            cdnAddress = ret;
            SaveCDNAddr();
        }
        if(GUILayout.Button("Copy到CDN", GUILayout.Width(100)))
        {
            CopyToCDN();
        }
        GUILayout.EndHorizontal();
        GUILayout.EndVertical();
    }

    static void CopyToCDN()
    {
        string dest =  Basic.Assist.CombineWithBSlash(cdnAddress, GetPlatformString());
        string src = Basic.Assist.CombineWithBSlash(GameConfig.BuildOption.localABFloder, GetPlatformString());
        Basic.Assist.CopyFloder(src, dest, true, true, true, new string[] { ".manifest" });
    }

    public static void ClearGarbageAB()
    {
        ClearUnuseAB(GetABFloder());
    }

    public static void SetABName(string path, string abname)
    {
        AssetImporter importer = AssetImporter.GetAtPath(path);
        if (importer)
        {
            //if (Basic.WithExtension(path, mustOneABExtensions))
            //abname = AResourceLoader.GenerateABNameByPath(path);

            if (importer.assetBundleName == abname)
                return;
            importer.assetBundleName = abname;
        }
    }



    public static BuildTarget buildTarget
    {
        get
        {
            return mBuildTarget;
        }
        set
        {
            mBuildTarget = value;
        }
    }

    static void ClearAll()
    {
        if (Directory.Exists(GetABFloder()))
            Directory.Delete(GetABFloder());
    }

    public static void BuildAB()
    {
        BuildAssetsBundles(true);
    }

    public static bool IsAndroid()
    {
        return mBuildTarget == BuildTarget.Android;
    }

    public static string GetPlatformString()
    {
        string platform = string.Empty;

        switch (mBuildTarget)
        {
            case BuildTarget.Android:
            {
                platform = GamePlatform.android.ToString();
            }
            break;
            case BuildTarget.iOS:
            {
                platform = GamePlatform.ios.ToString();
            }
            break;
            case BuildTarget.StandaloneWindows64:
            {
                platform = GamePlatform.pc.ToString();
            }
            break;
            default:
            {
                throw new Exception("Unknown Platform!");
            }
            break;
        }
        return platform;
    }

    public static string GetABFloder()
    {
        string ret = Basic.Assist.CombineWithBSlash(GameConfig.BuildOption.localABFloder, GetPlatformString(), GameConfig.BuildOption.abFloder);
        Basic.Assist.CreateDirectoryIfNotExist(ret);
        return ret;
    }



    public static void BuildAssetsBundles(bool exportIndex)
    {
        BuildAssetBundleOptions options = BuildAssetBundleOptions.DeterministicAssetBundle
                                          | BuildAssetBundleOptions.ChunkBasedCompression
                                          ;
        var ret = BuildPipeline.BuildAssetBundles(GetABFloder(), options, mBuildTarget);

        ExportABHashs(ret);
        if(exportIndex)
            ExportIndex();
    }

    static void SaveABIndex()
    {
        CheckInvalidResource();
        Basic.Assist.SaveJsonObject(mABIndex, GetIndexFileWithTarget(), GameConfig.BuildOption.abIndexCompressed);
    }

    public static string GetNameFromGame(string pathOrABName)
    {
        if(pathOrABName == ABContent.scriptABName || pathOrABName == ABContent.shaderABName)
        {
            return pathOrABName;
        }

        string abname = GameConfig.BuildOption.GenerateABNameByPath(pathOrABName);
        return abname;
    }

    public static void ExportABNames()
    {
        if (!TipFileNotExist(GameConfig.BuildOption.abDependenceFile))
            return;

        ABGraph graph = new ABGraph();
        var nodes = graph.LoadFromJson(GameConfig.BuildOption.abDependenceFile);
        nodes.Sort((a, b) => a.path.CompareTo(b.path));
        var contents = graph.GenerateContent(nodes);

        ABNameDefineSet defineSet = new ABNameDefineSet();
        foreach(var content in contents)
        {
            string sceneName = content.GetScene();
            if(string.IsNullOrEmpty(sceneName))
            {
                ABNameDefine def = new ABNameDefine();
                def.abName = GetNameFromGame(content.name);
                def.persistent = content.persistent;
                def.resources.AddRange(content.GetAllPaths());
                defineSet.defines.Add(def);
            }
            else
            {
                ABNameDefine sceneDef = new ABNameDefine();
                sceneDef.abName = GetNameFromGame("Scene_" + content.name);
                sceneDef.persistent = false;
                sceneDef.resources.Add(sceneName);
                defineSet.defines.Add(sceneDef);

                ABNameDefine def = new ABNameDefine();
                def.abName = GetNameFromGame(content.name);
                def.persistent = content.persistent;
                def.resources.AddRange(content.GetAllPathsWithoutScene());
                defineSet.defines.Add(def);
            }
        }

        //Cannot mark assets and scenes in one AssetBundle.


        string text = JsonUtility.ToJson(defineSet, true);
        File.WriteAllText(GameConfig.BuildOption.abNamesFile, text);
    }
    public static void ExportIndex()
    {
        abIndex.indices.Clear();
        ExportAssetIndex(abIndex.indices);
        SaveABIndex();
    }
    public static bool TipFileNotExist(string file)
    {
        if (File.Exists(file))
            return true;
        EditorUtility.DisplayDialog("Error", string.Format("File Not Exist:{0}", file), "OK");
        return false;
    }

    static ABNameDefineSet GetNameDefineSet()
    {
        if (!TipFileNotExist(GameConfig.BuildOption.abNamesFile))
            return null;
        string content = File.ReadAllText(GameConfig.BuildOption.abNamesFile);
        ABNameDefineSet defineSet = JsonUtility.FromJson<ABNameDefineSet>(content);
        return defineSet;
    }

    public static void SetAllABNames()
    {
        ABNameDefineSet defineSet = GetNameDefineSet();
        foreach (var def in defineSet.defines)
        {
            foreach (var path in def.resources)
                SetABName(path, def.abName);
        }
    }

    public static void ClearOldABNames()
    {
        AssetDatabase.RemoveUnusedAssetBundleNames();
        var names = AssetDatabase.GetAllAssetBundleNames();
        if (names == null || names.Length == 0)
            return;
        ABNameDefineSet defineSet = GetNameDefineSet();
        foreach (var name in names)
        {
            if (defineSet.defineMap.ContainsKey(name))
                continue;
            var paths = AssetDatabase.GetAssetPathsFromAssetBundle(name);
            if(paths == null || paths.Length == 0)
            {
                continue;
            }

            foreach(var path in paths)
            {
                AssetImporter importer = AssetImporter.GetAtPath(path);
                importer.assetBundleName = string.Empty;
            }
        }
        AssetDatabase.RemoveUnusedAssetBundleNames();
    }

    static List<string> GetErrorABSource(string abname)
    {
        List<string> ret = new List<string>();
        if (abIndex.indices.Count == 0)
            return ret;
        foreach(var item in abIndex.indices)
        {
            if (item.v == abname)
                ret.Add(item.k);
        }
        return ret;
    }

    public static void ExportABHashs(AssetBundleManifest mainfest, List<AB> abs = null)
    {
        bool save = abs == null;
        if (abs == null)
        {
            abs = abIndex.abs;
        }

        abIndex.abs.Clear();

        AssetDatabase.RemoveUnusedAssetBundleNames();
        var names = AssetDatabase.GetAllAssetBundleNames();

        ABNameDefineSet defineSet = GetNameDefineSet();

        List<string> garbages = new List<string>();

        foreach (var abName in names)
        {
            FileInfo fileInfo = new FileInfo(Basic.Assist.CombineWithSlash(GetABFloder(), abName));
            if(!fileInfo.Exists)
            {
                List<string> srcfiles = GetErrorABSource(abName);
                if(srcfiles.Count > 0)
                {
                    StringBuilder sb = new StringBuilder();
                    foreach(var file in srcfiles)
                    {
                        sb.Append(string.Format("Error AB Define=>{0},", file));
                    }
                    BuildLog.WriteLine(sb.ToString());
                }
                garbages.Add(abName);
            }
            else
            {
                AB info = new AB();
                info.name = abName;
                info.children.AddRange(mainfest.GetAllDependencies(abName));
                info.hash = mainfest.GetAssetBundleHash(abName).ToString();
                info.size = (int)fileInfo.Length;
                try
                {
                    info.persistent = defineSet.defineMap[abName].persistent;
                }
                catch (System.Exception ex)
                {
                    Debug.LogError(string.Format("Path Error! AB name:" + abName));
                }
                mABIndex.abs.Add(info);
            }
        }

        if (save)
            SaveABIndex();
    }
    public static  bool CheckError()
    {
        StringBuilder sb = new StringBuilder();
        bool error = false;
        foreach (var index in abIndex.indices)
        {
            if(index.v.Length == 0)
            {
                error = true;
                Debug.LogError(string.Format("Error:AB name is empty!({0})", index.k));
            }
        }
        if (!error)
            EditorUtility.DisplayDialog("", "没有错误！", "OK");
        return true;
    }
    public static void ExportAssetIndex(List<ResourceIndex> indices = null)
    {
        bool save = indices == null;
        if (indices == null)
        {
            indices = abIndex.indices;
        }

        abIndex.indices.Clear();

        string sDir = Path.Combine(Application.dataPath, GameConfig.BuildOption.ExternResourceFloder);
        DirectoryInfo dir = new DirectoryInfo(sDir);
        FileInfo[] files = dir.GetFiles("*.*", SearchOption.AllDirectories);

        int len = GameConfig.BuildOption.abResourceAssetFloder.Length;
        foreach (var file in files)
        {
            if (Basic.Assist.WithExtension(file.Name, resourceExtensionSet))
            {
                string path = Basic.Assist.ConvertToPathStartWithAsset(file.FullName);
                AssetImporter importer = AssetImporter.GetAtPath(path);
                ResourceIndex index = new ResourceIndex();
                index.k = path.Remove(0, len);
                if (importer)
                {
                    index.v = importer.assetBundleName;
                }
                indices.Add(index);
            }
        }

        if (save)
            SaveABIndex();
    }



    static string GetIndexFileWithTarget()
    {
        string ret = Basic.Assist.CombineWithBSlash(GameConfig.BuildOption.localABFloder, GetPlatformString(), GameConfig.BuildOption.abIndexFile);
        return ret;
    }

    public static void CheckInvalidResource()
    {
        List<AB> abs = new List<AB>();

        string path = ABExporter.GetABFloder();
        foreach (var item in abIndex.abs)
        {
            var filename = Path.Combine(path, item.name);
            if (File.Exists(filename))
                continue;
            abs.Add(item);
        }

        foreach (var item in abs)
        {
            abIndex.abs.RemoveAll((i) => i.name == item.name);
        }
    }

    public  static void ClearUnuseAB(string path)
    {
        DirectoryInfo directoryInfo = new DirectoryInfo(path);
        if (!directoryInfo.Exists)
            return;
        FileInfo[] files = directoryInfo.GetFiles("*.*", SearchOption.AllDirectories);

        for (int i = 0; i < files.Length; ++i)
        {
            var file = files[i];
            string fname = file.Name;
            fname = Path.GetFileNameWithoutExtension(file.Name);
            if (fname == "ab")
                continue;
            if (abIndex.abMap.ContainsKey(fname))
                continue;
            File.Delete(file.FullName);
        }
    }
    public static FileInfo[]  GetExternResources(string pattarn = "*.*")
    {
        string sDir = Path.Combine(Application.dataPath, GameConfig.BuildOption.ExternResourceFloder);
        DirectoryInfo dir = new DirectoryInfo(sDir);
        FileInfo[] files = dir.GetFiles(pattarn, SearchOption.AllDirectories);
        return files;
    }

    //[MenuItem("FF/BuildTool/ClearAllRef")]
    //public static void ClearObjectRef() {
    //    FileInfo[] files = GetAllPrefabs();
    //    int len = files.Length;
    //    for (int i = 0; i < len; ++i) {
    //        EditorUtility.DisplayProgressBar(string.Format("ADD({0}/{1})", i, len), "Add reference", (float)i / len);
    //        var file = files[i];
    //        string assetpath = Basic.Assist.ConvertToPathStartWithAsset(file.FullName);
    //        GameObject obj = AssetDatabase.LoadAssetAtPath<GameObject>(assetpath);
    //        var abref = obj.GetComponent<ABReference>();
    //        if (abref)
    //            UnityEngine.Object.DestroyImmediate(abref, true);
    //    }
    //    EditorUtility.ClearProgressBar();
    //    AssetDatabase.SaveAssets();
    //}

    public static FileInfo[] GetAllPrefabs()
    {
        DirectoryInfo dir = new DirectoryInfo(Application.dataPath);
        FileInfo[] files = dir.GetFiles("*.prefab", SearchOption.AllDirectories);
        return files;
    }

    [MenuItem("FF/BuildTool/CheckObjectRef")]
    public static void CheckObjectRef()
    {
        FileInfo[] files = GetAllPrefabs();
        int len = files.Length;
        for(int i = 0; i < len; ++i)
        {
            EditorUtility.DisplayProgressBar(string.Format("ADD({0}/{1})", i, len), "Add reference", (float)i / len);
            var file = files[i];
            string assetpath = Basic.Assist.ConvertToPathStartWithAsset(file.FullName);

            AssetImporter importer = AssetImporter.GetAtPath(assetpath);
            GameObject obj = AssetDatabase.LoadAssetAtPath<GameObject>(assetpath);
            if (!string.IsNullOrEmpty(importer.assetBundleName))
            {
                var abref = obj.TryGetComponent<ABReference>();
                if (abref.abName != importer.assetBundleName)
                    abref.abName = importer.assetBundleName;
            }
            else
            {
                var abref = obj.GetComponent<ABReference>();
                if (abref)
                    UnityEngine.Object.DestroyImmediate(abref, true);
            }
        }
        EditorUtility.ClearProgressBar();
        AssetDatabase.SaveAssets();
    }
    [MenuItem("FF/BuildTool/CheckInvalidReference")]
    public static void CheckInvalidReference()
    {
        string sDir = Path.Combine(Application.dataPath, "Resources");
        DirectoryInfo dir = new DirectoryInfo(sDir);
        FileInfo[] files = dir.GetFiles("*.*", SearchOption.AllDirectories);

        Dictionary<string, OneResource> allresources = new Dictionary<string, OneResource>();

        string parentFloder = Path.GetDirectoryName(Application.dataPath);

        foreach (var file in files)
        {
            if (Basic.Assist.WithExtension(file.Name, ABExporter.resourceExtensionSet))
            {
                string path = Basic.Assist.ConvertToPathStartWithAsset(file.FullName);
                string curguid = AssetDatabase.AssetPathToGUID(path);
                if (allresources.ContainsKey(curguid))
                    continue;
                AddDepend(file, allresources);
            }
        }

        const string floader = "Assets/Resources";

        HashSet<string> invalidResources = new HashSet<string>();
        foreach (var res in allresources)
        {
            foreach (var path in res.Value.dependices)
            {
                if (!path.StartsWith(floader) && res.Value.path.StartsWith(floader))
                {
                    invalidResources.Add(path + " :: " + res.Value.path);
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        foreach (var item in invalidResources)
        {
            sb.AppendLine(item);
        }

        File.WriteAllText(GameConfig.BuildOption.innerDependenceFile, sb.ToString());
    }

    [MenuItem("FF/BuildTool/GenerateDepencices")]
    public static void GenerateDepencices()
    {
        string sDir = Path.Combine(Application.dataPath, GameConfig.BuildOption.ExternResourceFloder);
        DirectoryInfo dir = new DirectoryInfo(sDir);
        FileInfo[] files = dir.GetFiles("*.*", SearchOption.AllDirectories);

        Dictionary<string, OneResource> allresources = new Dictionary<string, OneResource>();

        string parentFloder = Path.GetDirectoryName(Application.dataPath);

        foreach (var file in files)
        {
            if (Basic.Assist.WithExtension(file.Name, ABExporter.resourceExtensionSet))
            {
                string path = Basic.Assist.ConvertToPathStartWithAsset(file.FullName);
                string curguid = AssetDatabase.AssetPathToGUID(path);
                if (allresources.ContainsKey(curguid))
                    continue;
                AddDepend(file, allresources);
            }
        }

        ResourceSet rs = new ResourceSet();
        foreach (var item in allresources)
        {
            rs.resources.Add(item.Value);
        }
        Basic.Assist.CreateDirectoryIfNotExist(Path.GetDirectoryName(GameConfig.BuildOption.abDependenceFile));
        string content = JsonUtility.ToJson(rs, true);
        File.WriteAllText(GameConfig.BuildOption.abDependenceFile, content);
    }

    static void AddDepend(FileInfo file, Dictionary<string, OneResource> allresources)
    {
        string path = Basic.Assist.ConvertToPathStartWithAsset(file.FullName);
        string curguid = AssetDatabase.AssetPathToGUID(path);
        OneResource current = TryGetOneResource(curguid, path, allresources);
        string[] dependencies = AssetDatabase.GetDependencies(path);
        if (dependencies != null && dependencies.Length > 0)
        {
            foreach (var dep in dependencies)
            {
                if (!dep.EndsWith(".cs") && !dep.EndsWith(".js"))
                {
                    if (current.dependices.Contains(dep))
                        continue;
                    string guid = AssetDatabase.AssetPathToGUID(dep);
                    OneResource dep_resource = TryGetOneResource(guid, dep, allresources);
                    dep_resource.reference++;
                    current.dependices.Add(dep);
                }
            }

            foreach (var dep in dependencies)
            {
                if (!dep.EndsWith(".cs") && !dep.EndsWith(".js"))
                {
                    string guid = AssetDatabase.AssetPathToGUID(dep);
                    if (dep.ToLower() == path.ToLower())
                        continue;
                    FileInfo childfile = new FileInfo(dep);
                    AddDepend(childfile, allresources);
                }
            }
        }
    }


    static OneResource TryGetOneResource(string guid, string path, Dictionary<string, OneResource> allresources)
    {
        OneResource or = null;
        if (!allresources.TryGetValue(guid, out or ))
        {
            or = new OneResource();
            or.guid = guid;
            or.path = path;
            allresources.Add(guid, or );
        }
        return or;
    }
}
