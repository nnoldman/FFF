using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FairyGUI;
using UnityEngine;

public class ChatView : View
{
    private Chat.Main window_;
    private List<Cmd.RetMessage> histroy_;
    private bool viewLately_ = true;

    protected override string GetPackageName()
    {
        return "Chat/Main";
    }
    protected override void OnCreate()
    {
        this.window_ = (Chat.Main)this.contentPane;
        this.window_.list_.SetVirtual();
        this.window_.list_.itemProvider = ItemProvider;
        this.window_.list_.itemRenderer = ItemRenderer;

        this.window_.send_.onClick.Add(OnCommand);
        this.window_.emotion_.onClick.Add(OnCommand);

        this.window_.input_.onKeyDown.Add(__inputKeyDown1);
        histroy_ = MessageSystem.Instance.GetHistroy();
        InitHistroy();
    }
    void __inputKeyDown1(EventContext context)
    {
        if (context.inputEvent.keyCode == KeyCode.Return)
            this.SendMessage();
    }

    protected override void OnCommand(EventContext context)
    {
        base.OnCommand(context);
        if(this.window_.emotion_ == context.sender)
        {

        }
        else if(this.window_.send_ == context.sender)
        {
            this.SendMessage();
        }
    }

    void SendMessage()
    {
        if (this.window_.input_.text.Length == 0)
            return;

        Cmd.ReqChat cmd = new Cmd.ReqChat();
        cmd.channel = Cmd.MessageChannel.MessageChannel_User_World;
        cmd.from = LoginSystem.Instance.currentRole.name;
        cmd.roleID = LoginSystem.Instance.currentRole.id;
        cmd.content = this.window_.input_.text;
        Nets.Send(Cmd.CLIENTID.RQChat, cmd);
    }

    void ItemRenderer(int index, GObject item)
    {
        var data = histroy_[index];
        var go = item.asButton;
        go.icon = UnityEngine.Random.Range(200, 300).ToString();
        go.title = data.content;
        item.data = data;
    }

    string ItemProvider(int index)
    {
        var msg = histroy_[index];
        if (msg.sender == LoginSystem.Instance.currentRole.name)
            return "ui://Chat/ChatItemRight";
        else
            return "ui://Chat/ChatItemLeft";
    }

    void InitHistroy()
    {
        if (histroy_.Count == 0)
            return;
        for(int i = 0; i < histroy_.Count; ++i)
        {
            AddMessage(histroy_[i]);
        }
    }

    protected override void BindListeners()
    {
        GameEvents.Instance.Bind(GameEventID.OnMessageChat, OnMessage);
    }

    void AddMessage(Cmd.RetMessage msg)
    {
        this.window_.list_.numItems = this.histroy_.Count;
        if (viewLately_)
            this.window_.list_.scrollPane.ScrollBottom();
    }

    void OnMessage(object args)
    {
        var message = (Cmd.RetMessage)args;
        //histroy_.Add(message);
        AddMessage(message);
    }

    protected override void OnShowMe()
    {
    }

    protected override void OnHideMe()
    {
    }
}
