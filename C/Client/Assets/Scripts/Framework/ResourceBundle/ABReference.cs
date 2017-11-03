using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class ABReference : MonoBehaviour
{
    public string abName = string.Empty;

#if UNITY_EDITOR
    public int reference = 0;
    [ContextMenu("CalReference")]
    public void CalReference()
    {
        reference = ResourceProcedure.Instance.GetRef(abName);
    }
#endif

#if LOAD_FROM_AB
    void Awake()
    {
        ResourceProcedure.Instance.AddRef(abName);
    }

    void OnDestroy()
    {
        if (ResourceProcedure.Instance.DecRef(abName) == 0)
        {
            //Debug.LogWarning("Unload AB:" + abName);
            ResourceProcedure.Instance.UnloadGarbage(abName);
        }
    }
#endif
}
