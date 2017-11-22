using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameFrame {

public enum ShowMode {
    None,
    FullScreen,
    Window,
    Model,
}

public class ViewBase : Window {
    public UIPanel panel;
    public bool goBackWhenClickBG = true;
    protected virtual void BindListeners() {
    }

    protected virtual void RemoveEvents() {
    }

    protected virtual void OnShowMe() {
    }
    protected virtual void OnHideMe() {
    }
    protected sealed override void OnInit() {
        var text = GetPackageName();
        var elements = text.Split('/');
        var package = elements[0];
        var name = elements[1];
        UIPackage.AddPackage(GameConfig.FairyGUIOption.PackagePath + package);
        this.contentPane = UIPackage.CreateObject(package, name).asCom;
        this.contentPane.onClick.Add(OnCommand);
        this.OnCreate();
    }
    protected virtual string GetPackageName() {
        throw new System.NotImplementedException();
    }
    protected virtual void OnCreate() {

    }
    protected virtual void OnCommand(EventContext context) {
        if (context.initiator == this.contentPane.container) {
            if(goBackWhenClickBG)
                UIs.Instance.GoBack();
        }
    }
    protected sealed override void OnHide() {
        //this.panel.gameObject.SetActive(false);
        this.OnHideMe();
        this.RemoveEvents();
    }

    protected override sealed void OnShown() {
        //this.panel.gameObject.SetActive(true);
        this.OnShowMe();
        this.BindListeners();
    }

    public void ShowWindow(bool only = true) {
        UIs.Instance.ShowView(this, only);
    }
}


public interface INetUser {
}

}
