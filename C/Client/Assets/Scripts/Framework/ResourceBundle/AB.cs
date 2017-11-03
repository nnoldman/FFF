using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

[Serializable]
public class AB
{
    public string name;
    public string hash;
    public int size;
    public bool persistent;
    public List<string> children = new List<string>();
}
[Serializable]
public class GameVersion
{
    public int main = 1;
    public int program = 0;
    public int resource = 0;
    public string time;

    public bool ProgramHigherThan(GameVersion b)
    {
        if (b == null)
            return true;
        if (this.main > b.main)
            return true;
        if (this.main == b.main && this.program > b.program)
            return true;
        return false;
    }

    public bool ResourceHigherThan(GameVersion b)
    {
        if (ProgramHigherThan(b))
            return true;
        if (this.main >= b.main && this.program >= b.program && this.resource > b.resource)
            return true;
        return false;
    }

    public bool HigherThan(GameVersion b)
    {
        if (ProgramHigherThan(b))
            return true;
        return ResourceHigherThan(b);
    }

    public override string ToString()
    {
        return string.Format("{0}.{1}.{2}", main, program, resource);
    }
    public static GameVersion Parse(string content)
    {
        GameVersion version = new GameVersion();
        try
        {
            var strs = content.Split(new char[1] { '.' });
            if (strs.Length > 0)
                version.main = int.Parse(strs[0]);
            if (strs.Length > 1)
                version.program = int.Parse(strs[1]);
            if (strs.Length > 2)
                version.resource = int.Parse(strs[2]);
        }
        catch(Exception exc)
        {
            //ALog.Error(exc.Message);
        }
        return version;
    }

    public bool Equals(GameVersion rhs)
    {
        return this.main == rhs.main && this.program == rhs.program && this.resource == rhs.resource;
    }
}

public enum GamePlatform
{
    pc,
    android,
    ios,
}

[Serializable]
public class ABIndex
{
    public List<AB> abs = new List<AB>();
    public List<ResourceIndex> indices = new List<ResourceIndex>();

    [System.NonSerialized]
    Dictionary<string, AB> mABNameMap = null;

    [System.NonSerialized]
    Dictionary<string, string> mIndexMap = null;

    public Dictionary<string, AB> abMap
    {
        get
        {
            if (mABNameMap == null)
            {
                mABNameMap = new Dictionary<string, AB>();
                foreach (var info in abs)
                {
                    mABNameMap.Add(info.name, info);
                }
            }
            return mABNameMap;
        }
    }

    public Dictionary<string, string> indexMap
    {
        get
        {
            if (mIndexMap == null)
            {
                mIndexMap = new Dictionary<string, string>();
                foreach (var info in indices)
                {
                    mIndexMap.Add(info.k.ToLower(), info.v);
                }
            }
            return mIndexMap;
        }
    }
}

public class ABTaker
{
    public AssetBundle ab;
    public UnityEngine.Object obj;
    public string name;
    public bool persistent = false;

    List<ABTaker> parents = new List<ABTaker>();
    List<ABTaker> children = new List<ABTaker>();

    public bool isGarbage
    {
        get
        {
            return reference == 0 && !persistent;
        }
    }

    public bool isScene
    {
        get
        {
            return ab.isStreamedSceneAssetBundle;
        }
    }

    public int reference
    {
        get
        {
            return mReference;
        }
    }

    public override string ToString()
    {
        return name + ":" + mReference.ToString();
    }

    public int AddReference()
    {
        mReference++;
        for (int i = 0; i < children.Count; ++i)
            children[i].AddReference();
#if UNITY_EDITOR
        if(mReference == 0)
        {
            if(parents.Count > 0)
            {
                for(int i = 0; i < parents.Count; ++i)
                {
                    Debug.Assert(parents[i].reference == 0);
                }
            }
        }
#endif
        return mReference;
    }

    public int DecReference()
    {
        --mReference;
        for (int i = 0; i < children.Count; ++i)
            children[i].DecReference();
        return mReference;
    }

    public void AddChild(ABTaker taker)
    {
        if (children.Contains(taker))
            return;
        children.Add(taker);

        if (taker.parents.Contains(this))
            return;
        taker.parents.Add(this);
    }

    public void Destroy(bool force = false)
    {
        if(!force)
            Debug.Assert(isGarbage);
        ab.Unload(true);
    }

    private int mReference = 0;

}
