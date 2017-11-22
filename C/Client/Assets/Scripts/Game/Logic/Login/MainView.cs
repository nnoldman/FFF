using GameFrame;
using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class MainView : View {
    MainUI.MainWindow window;
    protected override string GetPackageName() {
        return "MainUI/MainWindow";
    }
    protected override void OnCreate() {
        this.goBackWhenClickBG = false;
        window = (MainUI.MainWindow)this.contentPane;
        this.window.bm1_.onClick.Add(OnCommand);
        this.window.bm2_.onClick.Add(OnCommand);
        this.window.bm3_.onClick.Add(OnCommand);
        this.window.bm4_.onClick.Add(OnCommand);
        this.window.bm5_.onClick.Add(OnCommand);
    }
    protected override void OnCommand(EventContext context) {
        if (context.sender == this.window.bm1_) {
            UIs.Instance.Show<EarthView>(false);
        } else if (context.sender == this.window.bm2_) {
            var param = new Message.MessageBoxParam();
            param.content = "FFFFFFFFFFFFFFFFFFFFFFFF";
            Message.ShowBox(param);
        } else if (context.sender == this.window.bm3_) {
            UIs.Instance.Show<BagView>(false);
        } else if (context.sender == this.window.bm4_) {
            UIs.Instance.Show<ChatView>(false);
        } else if (context.sender == this.window.bm5_) {
        }
    }
    protected override void OnShowMe() {
        UpdateBase();
    }

    void UpdateBase() {
        this.window.name_.text = LoginSystem.Instance.currentRole.name;
        var timeline = HeroSystem.Instance.timeline;
        var record = TimeTable.Instance.Get(timeline.trun + 1);
        this.window.time_.text = record.period;
    }
}
