using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Commands : Dispatcher
{
    public static Commands Instance
    {
        get
        {
            if (smInstance == null)
            {
                smInstance = new Commands();
            }
            return smInstance;
        }
    }
    public static Commands smInstance;

    public void Bind(Cmd.SERVERID id, Action<object> callback)
    {
        Bind((int)id, callback);
    }
    public void Trigger(Cmd.SERVERID id, object args)
    {
        Trigger((int)id, args);
    }
}