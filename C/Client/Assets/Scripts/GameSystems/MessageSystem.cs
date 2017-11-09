using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class MessageSystem: SystemBase
{
    public static MessageSystem Instance;

    public Cmd.RetTimeLine timeline;
    private List<Cmd.RetMessage> histroy_ = new List<Cmd.RetMessage>();

    public override void BindListeners()
    {
        Commands.Instance.Bind(Cmd.SERVERID.RTMessage, OnMessage);
    }
    public List<Cmd.RetMessage> GetHistroy()
    {
        return this.histroy_;
    }
    void OnMessage(object pb)
    {
        var ret = ParseCmd<Cmd.RetMessage>(pb);
        Debug.LogWarning(string.Format("OnMessage:({0}){1}", ret.channel.ToString(), ret.content));
        switch(ret.channel)
        {
            case Cmd.MessageChannel.MessageChannel_System_TV:
            {
                GameEvents.Instance.Trigger(GameEventID.OnMessageTV, ret.content);
            }
            break;
        }
        histroy_.Add(ret);
        while (histroy_.Count > ClientDefine.HistroyCount.Chat)
            histroy_.RemoveAt(0);
        GameEvents.Instance.Trigger(GameEventID.OnMessageChat, ret);
    }
}
