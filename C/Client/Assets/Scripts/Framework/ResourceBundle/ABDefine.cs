using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum ABDefineType {
    UnSettinged = 0,
    Ignore = 1 << 1,
    OnePerFile = 1 << 2,
    OnePerFloder = 1 << 3,
    OnePerName = 1 << 4,
}

[System.Serializable]
public class ABDefine {
    public ABDefineType type = ABDefineType.UnSettinged;
    public string path;
    public bool persistent = false;
    public bool expend = false;

    public List<ABDefine> children;
}

[System.Serializable]
public class ABDefineSet {
    public List<ABDefine> children = new List<ABDefine>();

    public void CopyFrom(ABDefineSet src) {
        Dictionary<string, ABDefine> maps = new Dictionary<string, ABDefine>();
        foreach (var item in src.children) {
            AddToMap(item, maps);
        }

        foreach (var item in this.children) {
            SetDefine(item, maps);
        }
    }

    void SetDefine(ABDefine def, Dictionary<string, ABDefine> maps) {
        ABDefine src = null;
        if (maps.TryGetValue(def.path, out src)) {
            def.expend = src.expend;
            def.type = src.type;
            def.persistent = src.persistent;
        }
        if (def.children != null && def.children.Count > 0) {
            foreach (var child in def.children)
                SetDefine(child, maps);
        }
    }

    void AddToMap(ABDefine def, Dictionary<string, ABDefine> maps) {
        if (!maps.ContainsKey(def.path))
            maps.Add(def.path, def);
        if (def.children.Count > 0) {
            foreach (var child in def.children)
                AddToMap(child, maps);
        }
    }
}



[System.Serializable]
public class ResourceIndex {
    public string k = string.Empty;
    public string v = string.Empty;
}


public class ResourceNode {
    public string path;
    public string abName;
    public List<ResourceNode> dependices = new List<ResourceNode>();
    public List<ResourceNode> owners = new List<ResourceNode>();
}

[System.Serializable]
public class OneResource : IComparable {
    public string path;
    public string guid;
    public int reference;
    public List<string> dependices = new List<string>();

    public int CompareTo(object obj) {
        return CompareTo((OneResource)obj);
    }

    public int CompareTo(OneResource other) {
        if (this.reference > other.reference)
            return 1;
        if (this.reference < other.reference)
            return -1;
        return 0;
    }
}

[System.Serializable]
public class ResourceSet {
    public List<OneResource> resources = new List<OneResource>();
}

[System.Serializable]
public class ABNameDefine {
    public string abName;
    public List<string> resources = new List<string>();
    public bool persistent = false;
}

[System.Serializable]
public class ABNameDefineSet {
    public List<ABNameDefine> defines = new List<ABNameDefine>();

    public Dictionary<string, ABNameDefine> defineMap {
        get {
            if(mDefineMap == null) {
                mDefineMap = new Dictionary<string, ABNameDefine>();
                foreach (var def in defines) {
                    mDefineMap.Add(def.abName, def);
                }
            }
            return mDefineMap;
        }
    }
    private Dictionary<string, ABNameDefine> mDefineMap;
}




