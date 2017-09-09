using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AppCore
{

public enum ShowMode
{
    None,
    FullScreen,
    Window,
    Model,
}

public class ViewBase : Window
{
    public UIPanel panel;

    protected virtual void BindListeners()
    {
    }

    protected virtual void RemoveEvents()
    {
    }

    protected virtual void OnShowMe()
    {
    }
    protected virtual void OnHideMe()
    {
    }

    protected sealed override void OnHide()
    {
        this.panel.gameObject.SetActive(false);
        this.OnHideMe();
        this.RemoveEvents();
    }

    protected override sealed void OnShown()
    {
        this.panel.gameObject.SetActive(true);
        this.OnShowMe();
        this.BindListeners();
    }

    public void ShowWindow(bool only=true)
    {
        if(only)
            UIController.Instance.Close();
        this.Show();
    }
}


public interface INetUser
{
}

}
