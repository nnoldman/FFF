using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;



public class ABTaker {
    public AssetBundle ab;
    public UnityEngine.Object obj;
    public string name;
    public bool persistent = false;

    List<ABTaker> parents = new List<ABTaker>();
    List<ABTaker> children = new List<ABTaker>();

    public bool isGarbage {
        get {
            return reference == 0 && !persistent;
        }
    }

    public bool isScene {
        get {
            return ab.isStreamedSceneAssetBundle;
        }
    }

    public int reference {
        get {
            return mReference;
        }
    }

    public override string ToString() {
        return name + ":" + mReference.ToString();
    }

    public int AddReference() {
        mReference++;
        for (int i = 0; i < children.Count; ++i)
            children[i].AddReference();
#if UNITY_EDITOR
        if(mReference == 0) {
            if(parents.Count > 0) {
                for(int i = 0; i < parents.Count; ++i) {
                    Debug.Assert(parents[i].reference == 0);
                }
            }
        }
#endif
        return mReference;
    }

    public int DecReference() {
        --mReference;
        for (int i = 0; i < children.Count; ++i)
            children[i].DecReference();
        return mReference;
    }

    public void AddChild(ABTaker taker) {
        if (children.Contains(taker))
            return;
        children.Add(taker);

        if (taker.parents.Contains(this))
            return;
        taker.parents.Add(this);
    }

    public void Destroy(bool force = false) {
        if(!force)
            Debug.Assert(isGarbage);
        ab.Unload(true);
    }

    private int mReference = 0;

}
