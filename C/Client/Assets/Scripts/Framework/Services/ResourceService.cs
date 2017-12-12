using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UnityEngine;

public class ResourceService : Frame.Service<ResourceService> {
    Dictionary<string, ABTaker> takerMap_ = new Dictionary<string, ABTaker>();

    public override string GetTipText() {
        return "处理资源中。。。";
    }

    public int AddRef(string abName) {
        if(string.IsNullOrEmpty(abName)) {
            Debug.LogError("Empty AB");
            return 0;
        }

        ABTaker mainTaker;
        if(!takerMap_.TryGetValue(abName, out mainTaker)) {
            Debug.LogError("Error AB:" + abName);
            return 0;
        }
        return mainTaker.AddReference();
    }

    public int GetRef(string abName) {
        ABTaker taker;
        if (takerMap_.TryGetValue(abName, out taker))
            return taker.reference;
        return 0;
    }

    public int DecRef(string abName) {
        if (string.IsNullOrEmpty(abName)) {
            Debug.LogError("Empty AB");
            return 0;
        }

        ABTaker mainTaker;
        if (!takerMap_.TryGetValue(abName, out mainTaker)) {
            Debug.LogError("Error AB:" + abName);
            return 0;
        }
        return mainTaker.DecReference();
    }

    public void UnloadGarbage(string abName) {
        ABTaker taker;
        if (!takerMap_.TryGetValue(abName, out taker)) {
            Debug.LogError("Empty AB");
            return;
        }
        if (taker.isGarbage) {
            taker.Destroy();
            takerMap_.Remove(abName);
        }
    }

    public void UnloadAsset(string pathfile) {
        string abName = VersionService2.Instance.GetABName(pathfile);
        if (string.IsNullOrEmpty(abName))
            return;
        UnloadGarbage(abName);
    }

    //public void Destroy() {
    //    foreach (var kv in mABTakerMap) {
    //        ABTaker taker = kv.Value;
    //        taker.Destroy(true);
    //    }
    //    mABTakerMap.Clear();
    //    Resources.UnloadUnusedAssets();
    //}

    public void UnloadAllGarbage() {
        List<string> garbages = new List<string>();
        foreach (var kv in takerMap_) {
            ABTaker taker = kv.Value;
            if (taker.isGarbage) {
                garbages.Add(kv.Key);
            }
        }
        if (garbages.Count == 0)
            return;
        for (int i = 0; i < garbages.Count; ++i) {
            var name = garbages[i];
            ABTaker taker = takerMap_[name];
            taker.Destroy();
            takerMap_.Remove(name);
        }
        Resources.UnloadUnusedAssets();
    }

    static object mCacheLocker = new object();

    public T Create<T>(string path) where T : UnityEngine.Object {
        var prefab = Load<T>(path);
        if (prefab)
            return (T)UnityEngine.Object.Instantiate(prefab);
        return default(T);
    }

    public T Load<T>(string pathfile) where T : UnityEngine.Object {
#if LOAD_FROM_AB
        if(Application.isPlaying) {
            string abName = VersionService2.Instance.GetABName(pathfile);
            if(string.IsNullOrEmpty(abName)) {
                string path = Basic.Assist.TrimExtension(pathfile);
                return Resources.Load<T>(path);
            } else {
                return LoadInner<T>(abName, pathfile);
            }
        } else {
            return LoadFromAsset<T>(pathfile);
        }
#else
        return LoadFromAsset<T>(pathfile);
#endif
    }

    public T LoadFromAsset<T>(string pathfile) where T : UnityEngine.Object {
        string assetName = GameOption.BuildOption.Path2AssetName(pathfile);
        string path = Basic.Assist.CombineWithSlash(Path.GetDirectoryName(Application.dataPath), assetName);

        if(File.Exists(path)) {
            return LoadAsset<T>(assetName);
        } else {
            path = Basic.Assist.TrimExtension(pathfile);
            return Resources.Load<T>(path);
        }
    }

    void CacheAB(string name, ABTaker ab) {
        try {
            takerMap_.Add(name, ab);
        } catch (System.Exception ex) {
            Debug.LogError(ex.Message);
        }
        //Debug.Log("ADD AB:" + name);
    }

    T LoadAsset<T>(string assetPath) where T : UnityEngine.Object {
        UnityEngine.Object obj = null;
#if UNITY_EDITOR
        obj = UnityEditor.AssetDatabase.LoadAssetAtPath<UnityEngine.Object>(assetPath); ;
        return (T)obj;
#else
        return Resources.Load<T>(assetPath);
#endif
    }
    T CreateObjectFromAB<T>(ABTaker abtaker, string assetName) where T : UnityEngine.Object {
        if (abtaker.ab) {
            try {
                if (!abtaker.ab.isStreamedSceneAssetBundle) {
                    //if (abtaker.obj)
                    //    return (T)abtaker.obj;
                    //string name = Basic.Assist.TrimExtension(Path.GetFileName(assetName));
                    string name = Basic.Assist.CombineWithSlash(GameOption.BuildOption.abResourceAssetFloder, assetName).ToLower();
                    T ret = (T)abtaker.ab.LoadAsset(name);
                    //if(ret == null) {
                    //    Debug.LogWarning(string.Format("Asset Error:({0} , {1})", assetName, name));
                    //}
                    //Gen.ResetShader(ret);
                    abtaker.obj = ret;
                    return ret;
                } else {
                    //string[] scenePath = abtaker.ab.GetAllScenePaths();
                    //UnityEngine.Object myScene = ab.LoadAsset(scenePath[0]);
                }
            } catch (Exception exc) {
                Debug.LogError(exc.Message);
                return null;
            }
        }
        return null;
    }

    public ABTaker LoadDependenceFromDisk(string abName) {
        if (string.IsNullOrEmpty(abName)) {
            Debug.LogError("Empty ab:");
            return null;
        }
        ABTaker abtaker;
        if (takerMap_.TryGetValue(abName, out abtaker))
            return abtaker;

        string fullPath = Basic.Assist.CombineWithSlash(Frame.FrameOption.Files.sdABFloder, abName);
        if (File.Exists(fullPath)) {
            try {
                Basic.Assist.BeginWatch(abName);
                var data = File.ReadAllBytes(fullPath);
                abtaker = new ABTaker();
                //Debug.LogWarning("ABNAME:" + abName);
                abtaker.ab = AssetBundle.LoadFromMemory(data);
            } catch (Exception exc) {
                Debug.LogError(exc.Message);
            }
            Frame.ABFile info = VersionService2.Instance.GetAB(abName);
            abtaker.name = abName;
            abtaker.persistent = info.persistent;
            if (abtaker.persistent)
                abtaker.ab.LoadAllAssets();
            MakeChildren(abtaker);
            Basic.Assist.EndWatch();
            CacheAB(abName, abtaker);
            return abtaker;
        }
        return null;
    }

    public void OnSceneClose() {
        foreach (var kv in takerMap_)
            if (kv.Value.isScene)
                kv.Value.DecReference();

        UnloadAllGarbage();
    }

    void MakeChildren(ABTaker taker) {
        Frame.ABFile info = VersionService2.Instance.GetAB(taker.name);

        for (int i = 0; i < info.children.Count; ++i) {
            var name = info.children[i];

            ABTaker child = null;
            if (takerMap_.TryGetValue(name, out child)) {
                taker.AddChild(child);
            } else {
                Debug.Assert(child != null);
            }
        }
    }

    void LoadDependence(string abName) {
        List<string> abNames = new List<string>();
        GetAllDependencies(ref abNames, abName);

        for (int i = 0; i < abNames.Count; ++i) {
            string name = abNames[i];
            if (takerMap_.ContainsKey(name))
                continue;
            LoadDependenceFromDisk(name);
        }
    }

    T LoadInner<T>(string abName, string assetName) where T : UnityEngine.Object {
        if (string.IsNullOrEmpty(abName))
            return null;

        ABTaker abtaker;
        if (!takerMap_.TryGetValue(abName, out abtaker) || abtaker.ab == null) {
            if (abtaker != null && abtaker.ab == null)
                takerMap_.Remove(abName);
            LoadDependence(abName);
            takerMap_.TryGetValue(abName, out abtaker);
        }
        var ret = CreateObjectFromAB<T>(abtaker, assetName);
        AddReferenceCounter(ret, abtaker);
        return ret;
    }

    public void AddReferenceCounter<T>(T resource, ABTaker abTaker) where T : UnityEngine.Object {
        Type resourceType = resource.GetType();
        if (resourceType == typeof(GameObject)) {
            ABReference abref = (resource as GameObject).TryGetComponent<ABReference>();
            abref.abName = abTaker.name;
        } else if (resourceType == typeof(Texture2D)) {
            abTaker.persistent = true;
        } else if (resourceType == typeof(TextAsset)) {
            //abTaker.persistent = true;
        } else if (resourceType == typeof(AudioClip)) {
            //abTaker.persistent = true;
        } else {
            Debug.LogError("Error Resource Type:" + resourceType.Name);
        }
    }

    public void GetAllDependencies(ref List<string> names, string abName) {
        if (string.IsNullOrEmpty(abName))
            return;
        if (names.Contains(abName) || takerMap_.ContainsKey(abName))
            return;

        Frame.ABFile info = VersionService2.Instance.GetAB(abName);
        if (info != null) {
            for (int i = 0; i < info.children.Count; ++i) {
                GetAllDependencies(ref names, info.children[i]);
            }
        }
        names.Add(abName);
    }

    public bool IsABInMemory(string abName) {
        return takerMap_.ContainsKey(abName);
    }

    public void LoadAsync(Frame.IProgressBar owner, string tips, AsyncTasks tasks, Action onEnd = null) {
        Frame.Executer.SetProgressText(tips);
        owner.Show();
        Debug.Assert(false);
        //owner.StartCoroutine(InnerLoadAsync(tasks, onEnd));
    }

    IEnumerator InnerLoadAsync(AsyncTasks tasks, Action onEnd = null) {
        Basic.Assist.BeginWatch("LoadAsync");

        int len = 0;

        for (int i = 0; i < tasks.Count; ++i) {
            try {
                var task = tasks[i];
                task.CalcTargetCount();
                len += task.targetCount;
            } catch (System.Exception ex) {
                Debug.LogError(ex.Message);
            }
        }

        Debug.Log("Load AB Count: " + len.ToString());

        int cursor = 0;
        for (int i = 0; i < tasks.Count; ++i) {
            var task = tasks[i];
            for (int j = 0; j < task.targetCount; ++j) {
                task.DoStep(j);
                cursor++;
                Frame.Executer.SetProgress(cursor, len);
                yield return 0;
            }
        }

        if(len == 0) {
            Frame.Executer.SetProgress(1, 1);
            yield return 0;
        }

        if (onEnd != null)
            onEnd();
        Basic.Assist.EndWatch();
        yield return 0;
        Frame.Executer.HideProgressBar();
    }
}
