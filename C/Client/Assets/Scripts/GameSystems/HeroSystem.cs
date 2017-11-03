using AppCore;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class HeroSystem : SystemBase
{
    public static HeroSystem Instance;

    public Cmd.RetTimeLine timeline;

    public override void BindListeners()
    {
        Commands.Instance.Bind(Cmd.SERVERID.RTTimeLine, OnTimeLine);
    }

    void OnTimeLine(object pb)
    {
        var ret = ParseCmd<Cmd.RetTimeLine>(pb);
        timeline = ret;
        ShowMainUI();
    }

    void ShowMainUI()
    {
        UIController.Instance.mainView = UIController.Instance.Show<MainView>();
    }
}
