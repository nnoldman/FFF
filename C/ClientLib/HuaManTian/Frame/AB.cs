using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
[Serializable]
public class ABFile {
    public string name;
    public string hash;
    public int size;
    public bool persistent;
    public List<string> children = new List<string>();
}

public enum GamePlatform {
    pc,
    android,
    ios,
}
public class URLFile {
    public string url;
    public int size;
}
[System.Serializable]
public class ResourceIndex {
    public string k = string.Empty;
    public string v = string.Empty;
}
[Serializable]
public class AssetBundleIndex : IBoolObject {
    public GameVersion version = new GameVersion();
    public List<ABFile> files = new List<ABFile>();
    public List<ResourceIndex> indices = new List<ResourceIndex>();

    [System.NonSerialized]
    Dictionary<string, ABFile> fielNameMap_ = null;

    [System.NonSerialized]
    Dictionary<string, string> indexMap_ = null;

    public Dictionary<string, ABFile> abMap {
        get {
            if (fielNameMap_ == null) {
                fielNameMap_ = new Dictionary<string, ABFile>();
                foreach (var info in files) {
                    fielNameMap_.Add(info.name, info);
                }
            }
            return fielNameMap_;
        }
    }

    public Dictionary<string, string> indexMap {
        get {
            if (indexMap_ == null) {
                indexMap_ = new Dictionary<string, string>();
                foreach (var info in indices) {
                    indexMap_.Add(info.k.ToLower(), info.v);
                }
            }
            return indexMap_;
        }
    }
}
}
