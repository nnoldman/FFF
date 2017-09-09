using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class Loader : BaseController {
    public static Loader Instance {
        set;
        get;
    }

    public T Create<T>(string pathName) where T : UnityEngine.Object {
        var prefab = LoadPrefab<T>(pathName);
        if (prefab)
            return GameObject.Instantiate(prefab);
        return null;
    }

    public T LoadPrefab<T>(string pathName) where T : UnityEngine.Object {
        return (T)Resources.Load<T>(pathName);
    }


    public override IEnumerator initialize() {
        yield return null;
    }

    public override IEnumerator onGameStageClose() {
        yield return null;
    }
}
