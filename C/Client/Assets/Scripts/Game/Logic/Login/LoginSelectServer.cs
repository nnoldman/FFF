using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class LoginSelectServer : View {
    Login.SelectServer window;
    protected override string GetPackageName() {
        return "Login/SelectServer";
    }
    protected override void OnCreate() {
        window = (Login.SelectServer)this.contentPane;
        window.serverList.RemoveChildrenToPool();
        window.serverList.onClickItem.Add(OnSelectServer);
        window.enterGame.enabled = true;
        window.enterGame.onClick.Add(OnClickEnterGame);
        this.goBackWhenClickBG = false;
        for (int i = 0; i < GameOption.GameServers.Length; ++i) {
            var server = GameOption.GameServers[i];
            var item = (Login.ServerItem)window.serverList.AddItemFromPool().asCom;
            item.name_.text = server.name;
            item.data = server;
        }
        window.serverList.selectedIndex = 0;
        SetCurrentServer(window.serverList.selectedIndex);
    }

    void OnClickEnterGame() {
        var server = LoginSystem.Instance.currentServer;
        LoginSystem.Instance.LoginGame(server.host, server.port);
        window.enterGame.enabled = false;
    }

    void OnSelectServer(EventContext context) {
        SetCurrentServer(window.serverList.selectedIndex);
    }

    void SetCurrentServer(int index) {
        var server = GameOption.GameServers[index];
        LoginSystem.Instance.currentServer = server;
        this.window.currentServer.text = server.name;
    }

    protected override void OnShowMe() {
        SetCurrentServer(0);
    }
}
