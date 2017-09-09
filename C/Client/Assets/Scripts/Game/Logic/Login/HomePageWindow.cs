using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class HomePageWindow: View
{
    string host = "127.0.0.1";
    int ip = 15299;

    Login.LoginPlant window
    {
        get
        {
            return (Login.LoginPlant)this.panel.ui;
        }
    }

    public HomePageWindow()
    {
        Login.LoginBinder.BindAll();
    }

    protected override void OnInit()
    {
        window.login.onClick.Add(LoginPlant);
    }

    void LoginPlant()
    {
        LoginSystem.Instance.LoginPlant(host,ip,window.user.text, window.psw.text);
    }
}
