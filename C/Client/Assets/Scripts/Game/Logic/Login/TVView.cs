using GameFrame;
using DG.Tweening;
using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class TVView : View
{
    MainUI.TV window;
    public float duration = 10;

    private List<string> messages_ = new List<string>();
    private bool playing_ = false;
    private Vector3 sourcePositon_;
    protected override string GetPackageName()
    {
        return "MainUI/TV";
    }
    protected override void OnCreate()
    {
        window = (MainUI.TV)this.contentPane;
        sourcePositon_ = this.window.content_.position;
        this.sortingOrder = UILayer.TV;
        this.InvalidateBatchingState();
        GameEvents.Instance.Bind(GameEventID.OnTVMessage, OnTvMessage);
        this.Next();
    }

    void OnTvMessage(object args)
    {
        var content = (string)args;
        messages_.Add(content);
        if (!playing_)
            this.Next();
    }

    void Next()
    {
        this.HideImmediately();
        if (messages_.Count > 0)
        {
            this.Show();
            this.Center();
            playing_ = true;
            Play(messages_[0]);
            messages_.RemoveAt(0);
        }
        else
        {
            playing_ = false;
        }
    }

    void Play(string msg)
    {
        this.window.content_.text = msg;
        this.window.content_.position = new Vector3(this.window.width, sourcePositon_.y, sourcePositon_.z);
        var tweener = this.window.content_.TweenMoveX(-this.window.content_.width, duration);
        tweener.SetEase(Ease.Linear);
        tweener.OnComplete(Next);
    }
}
