using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using UnityEngine.SceneManagement;

public class AsyncLoadTask
{
    public string fileName;

    public int targetCount
    {
        get
        {
            return mTargetCount;
        }
    }

    protected int mTargetCount = 0;

    public virtual void DoStep(int i)
    {
    }

    public virtual void CalcTargetCount()
    {
        mTargetCount = 1;
    }
}

public class AsyncRequireLuaFile : AsyncLoadTask
{
    public override void DoStep(int i)
    {
        //App.Instance.LuaManager.MainState.DoString(String.Format("require '{0}'", fileName));
    }
}

public enum AsyncLoaderType
{
    None,
    InnerScene,
    InnerObject,
    Extern,
}

public class AsyncLoadGameObject: AsyncLoadTask
{
    public delegate void OnAssetLoaded(string name, UnityEngine.Object obj);

    public OnAssetLoaded onAssetLoaded;
    public AsyncLoaderType loaderType = AsyncLoaderType.None;
    List<string> mABNames;

    bool isInnerScene = false;

    public override void CalcTargetCount()
    {
        var updater = VersionProcedure.Instance;
        string abName = updater.GetABName(fileName);
        if(string.IsNullOrEmpty(abName) )
        {
            if (fileName.ToLower().EndsWith(".unity"))
                loaderType = AsyncLoaderType.InnerScene;
            else
            {
                loaderType = AsyncLoaderType.InnerObject;
                mTargetCount = 1;
            }
        }
        else
        {
            loaderType = AsyncLoaderType.Extern;
            mABNames = new List<string>();
            ResourceProcedure.Instance.GetAllDependencies(ref mABNames, abName);
            mTargetCount = mABNames.Count;
        }
    }

    public override void DoStep(int i)
    {

        if(loaderType == AsyncLoaderType.InnerScene)
        {

        }
        else if(loaderType == AsyncLoaderType.InnerObject)
        {
            string assetname = System.IO.Path.GetFileName(fileName).ToLower();
            var obj = ResourceProcedure.Instance.Load<UnityEngine.Object>(fileName);
            onAssetLoaded(fileName.ToLower(), obj);
        }
        else if (loaderType == AsyncLoaderType.Extern)
        {

            if (mTargetCount == 0)
                return;

            ABTaker abtaker = ResourceProcedure.Instance.LoadDependenceFromDisk(mABNames[i]);
            Debug.Assert(abtaker != null);
            if (abtaker == null)
                return;
            if (i == mTargetCount - 1)
            {
                if (abtaker.ab)
                {
                    if (abtaker.ab.isStreamedSceneAssetBundle)
                    {
                        abtaker.AddReference();
                    }
                    else if (onAssetLoaded != null)
                    {
                        string assetname = System.IO.Path.GetFileName(fileName).ToLower();
                        var obj = abtaker.ab.LoadAsset<UnityEngine.Object>(assetname);
                        ResourceProcedure.Instance.AddReferenceCounter(obj, abtaker);
                        onAssetLoaded(fileName.ToLower(), obj);
                    }
                }
            }
        }
    }
}

public class AsyncTasks : List<AsyncLoadTask>
{
}
