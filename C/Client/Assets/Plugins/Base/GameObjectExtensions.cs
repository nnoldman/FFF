using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public static class GameObjectExtensions
{
    public static Component TryGetComponent(this GameObject go, Type tp)
    {
        Component com = go.GetComponent(tp);
        if (!com)
            com = go.AddComponent(tp);
        return com;
    }
    public static T TryGetComponent<T>(this GameObject go) where T : Component
    {
        T com = go.GetComponent<T>();
        if (!com)
            com = go.AddComponent<T>();
        return com;
    }
}
