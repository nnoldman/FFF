using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

public class SystemBase
{
    public bool timeConsuming
    {
        get;
        protected set;
    }

    public SystemBase()
    {
        mSystems.Add(this);
        BindListeners();
    }

    public static List<SystemBase> mSystems = new List<SystemBase>();

    public static IEnumerator CloseGameSystems()
    {
        foreach (var system in mSystems)
        {
            system.CloseGameStage();
        }
        mSystems.Clear();
        yield return null;
    }

    public virtual IEnumerator Initialize()
    {
        yield return null;
    }

    public virtual void BindListeners()
    {

    }
    public virtual void CloseGameStage()
    {
    }

    public static T ParseCmd<T>(object args)
    {
        return ProtoBuf.Serializer.Deserialize<T>((MemoryStream)args);
    }
}
