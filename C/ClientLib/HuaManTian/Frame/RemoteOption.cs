using System;
using System.Collections.Generic;
using UnityEngine;

namespace Frame {
[Serializable]
public class RemoteRootOption: IBoolObject {
    public string cdn;
    public string serverList;
    public string appSite;
    public string lateServers;
    public GameVersion ios;
    public GameVersion android;

    public GameVersion CurrentVersion() {
        return Application.platform == RuntimePlatform.Android ? android : ios;
    }
}
}
