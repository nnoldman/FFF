using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using UnityEngine;

[Serializable]
public class URLInfo {
    public int id;
    public string name;
    public string url;
}

[Serializable]
public class URLInfoList {
    public List<URLInfo> infos = new List<URLInfo>();
}

public class NextStep {
    public System.Func<bool> condtion;
    public Step step;
}
public enum LoadingError {
    Success,
    ResourceLoginServerAddressConfigNotExist,
    RemoteURLConfigLoadFailedOrEmpty,
    RemoteCDNFloderGetFailed,
    RemoteVersionLoadFailedOrEmpty,
    RemoteIndexFileURLFailed,
    RemoteIndexLoadFailedOrEmpty,
    SDSaveVersionOrIndexFailed,
    StreamingLoadVersionError,
    StreamingLoadIndexError,
    PackageError,
    UnknownError,
}
public class Step {
    public System.Func<bool> exit;
    public LoadingError errorCode;
    public string name;
    public int id;
    public Action onEnd;

    public void AddNext(Step next, System.Func<bool> condtion) {
        NextStep ns = new NextStep();
        ns.step = next;
        ns.condtion = condtion;
        nexts.Add(ns);
    }

    public Step next {
        get {
            for (int i = 0; i < nexts.Count; ++i) {
                var child = nexts[i];
                if (child.condtion())
                    return child.step;
            }
            return null;
        }
    }

    public List<NextStep> nexts = new List<NextStep>();
}

public class DoNowStep: Step {
}

public class URLFile {
    public string url;
    public int size;
}

public class LoadOneStep : Step {
    public Func<string> getURL;
    public Action<WWW> loadDelegate;
}

public class LoadBeatchStep : Step {
    public Func<List<URLFile>> getURLs;
    public Action<WWW> loadDelegate;
}
