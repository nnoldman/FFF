using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class MessageSystem: SystemBase
{
    public static MessageSystem Instance;

    public Cmd.RetTimeLine timeline;

    public override void BindListeners()
    {
        Commands.Instance.Bind(Cmd.SERVERID.RTMessage, OnMessage);
    }

    void OnMessage(object pb)
    {
        var ret = ParseCmd<Cmd.RetMessage>(pb);
        Debug.LogWarning(string.Format("OnMessage:({0}){1}", ret.channel.ToString(), ret.content));
        switch(ret.channel)
        {
            case Cmd.MessageChannel.MessageChannel_System_TV:
            {
                GameEvents.Instance.Trigger(GameEventID.OnTVMessage, ret.content);
            }
            break;
        }
    }
}
