using GameFrame;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class GameServer {
    public string host;
    public string name;
    public int port;
    public int serverID;
}

public class LoginSystem: SystemBase {
    public static LoginSystem Instance;

    public bool ret;
    public string user;
    public string passWord;
    public int roleIndex;
    public LOGIN_RETURN_CODE returnCode;

    const string kUserKey = "__user";
    const string kPasswordKey = "__psw";

    public LoginSystem() {
        user = PlayerPrefs.GetString(kUserKey, string.Empty);
        passWord = PlayerPrefs.GetString(kPasswordKey, string.Empty);
    }
    public List<int> lateServerIDs = new List<int>();
    public GameServer currentServer;
    public Cmd.GameRole currentRole;

    private Connection accountConnection_;
    private Connection gameConnection_;

    private string user_;
    private string password_;
    private int accountID_;

    private Cmd.RetAccountOperation preOperation_;

    public void LoginPlant(string host, int port, string user, string psw) {
        var record = TimeTable.Instance.Get(5);
        user_ = user;
        password_ = psw;
        accountConnection_ = new Connection();
        accountConnection_.host = host;
        accountConnection_.port = port;
        accountConnection_.onConnectFailed = onConnectAccountFailed;
        accountConnection_.onConnectSucessed = onConnectAccountSucess;
        Nets.Instance.connect(accountConnection_);

        PlayerPrefs.SetString(kUserKey, user);
        PlayerPrefs.SetString(kPasswordKey, psw);
    }

    public void LoginGame(string host, int port) {
        gameConnection_ = new Connection();
        gameConnection_.host = host;
        gameConnection_.port = port;
        gameConnection_.onConnectFailed = onConnectGameFailed;
        gameConnection_.onConnectSucessed = onConnectGameSucess;
        Nets.Instance.connect(gameConnection_);
    }

    void onConnectGameFailed(SocketError error) {
        Debug.LogWarning("onConnectGameFailed:" + error.ToString());
    }

    void onConnectGameSucess() {
        Cmd.ReqLoginGameServer req = new Cmd.ReqLoginGameServer();
        req.time = preOperation_.time;
        req.token = preOperation_.token;
        req.accountid = preOperation_.accountid;
        Nets.Send(Cmd.CLIENTID.RQLoginGame, req);
    }

    void onConnectAccountSucess() {
        Cmd.ReqAccountOperation req = new Cmd.ReqAccountOperation();
        req.action = Cmd.AccountAction.AccountAction_Login;
        req.user = user_;
        req.password = password_;
        Nets.Send(Cmd.CLIENTID.RQAccountOperation, req);
    }

    void onConnectAccountFailed(SocketError error) {
        Debug.LogWarning("onConnectAccountFailed:" + error.ToString());
    }

    public override void BindListeners() {
        Commands.Instance.Bind(Cmd.SERVERID.RTAccountOperation, OnAccountReturn);
        Commands.Instance.Bind(Cmd.SERVERID.RTLoginGame, OnLoginGameReturn);
        Commands.Instance.Bind(Cmd.SERVERID.RTCreateRole, OnCreateRole);
    }

    public bool HasRole() {
        return currentRole != null && currentRole.id > 0;
    }
    void OnCreateRole(object pb) {
        var ret = ParseCmd<Cmd.RetCreateRole>(pb);
        Debug.Log("OnCreateRole:" + ret.error.ToString());
        currentRole = ret.role;
        ShowRoleView();
    }

    void ShowRoleView() {
        var window = UIs.Instance.Get<RoleView>();
        window.UpdateUI();
        window.ShowWindow();
    }

    void OnLoginGameReturn(object pb) {
        var ret = ParseCmd<Cmd.RetLoginGameServer>(pb);
        Debug.Log("OnLoginGameReturn:" + ret.error.ToString());
        currentRole = ret.role;
        ShowRoleView();
    }

    void OnAccountReturn(object pb) {
        Cmd.RetAccountOperation ret = ParseCmd<Cmd.RetAccountOperation>(pb);
        preOperation_ = ret;
        this.accountID_ = ret.accountid;
        this.lateServerIDs.Clear();
        this.lateServerIDs.AddRange(ret.late_serverids);
        foreach(var id in this.lateServerIDs) {
            if (id != 0) {
                currentServer = GameOption.GetServer(id);
                break;
            }
        }

        Debug.Log("RetAccountOperation:" + ret.accountid.ToString());
        UIs.Instance.Show<LoginSelectServer>();
    }
}
