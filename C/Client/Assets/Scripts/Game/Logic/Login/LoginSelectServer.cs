using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class LoginSelectServer : View
{
    Login.SelectServer window
    {
        get
        {
            return (Login.SelectServer)this.panel.ui;
        }
    }

    public LoginSelectServer()
    {
        Login.LoginBinder.BindAll();
    }

    protected override void OnInit()
    {
        window.serverList.RemoveChildrenToPool();
        window.serverList.onClickItem.Add(OnSelectServer);
        window.enterGame.onClick.Add(OnClickEnterGame);
        for (int i = 0; i < GameConfig.GameServers.Length; ++i)
        {
            var server = GameConfig.GameServers[i];
            var item = (Login.ServerItem)window.serverList.AddItemFromPool().asCom;
            item.name_.text = server.name;
            item.data = server;
        }
    }

    void OnClickEnterGame()
    {
        var server = LoginSystem.Instance.currentServer;
        LoginSystem.Instance.LoginGame(server.host, server.port);
    }

    void OnSelectServer(EventContext context)
    {
        var item = (Login.ServerItem)context.data;
        var server = (GameServer)item.data;
        LoginSystem.Instance.currentServer = server;
        SetCurrentServer();
    }

    void SetCurrentServer()
    {
        if (LoginSystem.Instance.currentServer !=null)
        {
            this.window.currentServer.text = LoginSystem.Instance.currentServer.name;
        }
        else
        {
            this.window.currentServer.text = string.Empty;
        }
    }

    protected override void OnShowMe()
    {
        SetCurrentServer();
    }
}
