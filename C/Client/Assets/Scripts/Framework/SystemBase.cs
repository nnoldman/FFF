using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

public class SystemBase
{
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

    public bool timeConsuming
    {
        protected set;
        get;
    }

    public SystemBase()
    {
        mSystems.Add(this);
        BindListeners();
    }

    public virtual void BindListeners()
    {
    }

    protected void BindCommand(Cmd.SERVERID id, Action<object> cmdHandler)
    {
        Commands.Instance.Bind(id, cmdHandler);
    }

    protected void BindEvent(GameEventID id, Action<object> cmdHandler)
    {
        GameEvents.Instance.Bind(id, cmdHandler);
    }

    public virtual IEnumerator Initialize()
    {
        yield return null;
    }
    public virtual IEnumerator CloseGameStage()
    {
        yield return null;
    }

    public static T ParseCmd<T>(object args)
    {
        return ProtoBuf.Serializer.Deserialize<T>((MemoryStream)args);
    }

}
