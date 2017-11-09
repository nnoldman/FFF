using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class HomePageWindow: View
{
    string host = "43.248.102.164";
    int ip = 15299;

    Login.LoginPlant window;
    protected override string GetPackageName()
    {
        return "Login/LoginPlant";
    }
    protected override void OnCreate()
    {
        this.goBackWhenClickBG = false;
        window = (Login.LoginPlant)this.contentPane;
        window.login.onClick.Add(LoginPlant);
    }

    void LoginPlant()
    {
        LoginSystem.Instance.LoginPlant(host, ip, window.user.text, window.psw.text);
    }
}
