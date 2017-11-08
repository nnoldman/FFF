using GameFrame;
using DG.Tweening;
using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class MessageBoxView : View
{
    private MessageBox.MessageBox window;

    private Message.MessageBoxParam param_;

    protected override string GetPackageName()
    {
        return "MessageBox/MessageBox";
    }
    protected override void OnCreate()
    {
        window = (MessageBox.MessageBox)this.contentPane;
        this.modal = true;
        this.window.cancel_.onClick.Add(OnLeftButtonClick);
        this.window.ok_.onClick.Add(OnRightButtonClick);
    }

    protected override void OnShowMe()
    {
        this.Center();
        //GRoot.inst.ShowModalWait();
    }
    protected override void OnHideMe()
    {
        //GRoot.inst.CloseModalWait();
    }

    public void Open(Message.MessageBoxParam param)
    {
        this.param_ = param;
        this.UpdateStates();
        this.ShowWindow(false);
    }

    void OnLeftButtonClick()
    {
        UIController.Instance.GoBack();
        if (this.param_.leftButtonCallback != null)
            this.param_.leftButtonCallback(this.param_.data);
    }
    void OnRightButtonClick()
    {
        UIController.Instance.GoBack();
        if (this.param_.rightButtonCallback != null)
            this.param_.rightButtonCallback(this.param_.data);
    }

    void UpdateStates()
    {
        if (this.param_.leftButtonText.Length > 0)
            this.window.cancel_.title = this.param_.leftButtonText;
        else
            this.window.cancel_.title = ClientDefine.ConstString.MessageBox.Cancel;
        if (this.param_.rightButtonText.Length > 0)
            this.window.ok_.title = this.param_.rightButtonText;
        else
            this.window.ok_.title = ClientDefine.ConstString.MessageBox.OK;
        this.window.content_.text = this.param_.content;
    }
}
