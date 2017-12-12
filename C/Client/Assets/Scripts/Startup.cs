using UnityEngine;
using System.Collections;
using GameFrame;
using FairyGUI;
using System.Reflection;
using System;
using System.Collections.Generic;

public class Startup : MonoBehaviour {
    Startup mInstance;
    Game game_ = new Game();

    void Awake() {
        Debug.Assert(mInstance == null);
        mInstance = this;

        Frame.Executer.SetProgressBar(GateWindow.Instance);
        Frame.Executer.SetMessageBox(GateBox.Instance);
        Frame.Executer.ShowProgressBar();

        Frame.Services.Instance.onProcess += Frame.Executer.SetProgress;
        Frame.Services.Instance.onTip += Frame.Executer.SetProgressText;

        Frame.Services.Instance.Clear();
        Frame.Services.Instance.AddService<GateUIService>();
        Frame.Services.Instance.AddService<Frame.VersionService>();
        Frame.Services.Instance.AddService<NetService>();
        Frame.Services.Instance.AddService<ResourceService>();
        Frame.Services.Instance.AddService<ConfigService>();
        Frame.Services.Instance.AddService<PreloadService>();
        Frame.Services.Instance.AddService<GameSystemsServie>();
        Frame.Services.Instance.AddService<LoginService>();
        Frame.Services.Instance.onStartEnd += OnStartEnd;

        StartCoroutine(Frame.Services.Instance.Start());
    }

    IEnumerator OnStartEnd() {
        this.game_.AddController<Nets>();
        this.game_.AddController<GameFrame.Icons>();
        this.game_.AddController<UIs>();
        this.game_.AddController<GameFrame.Cameras>();
        yield return this.game_.Start();
        UIs.Instance.Show<HomePageWindow>();

        Frame.Executer.HideProgressBar();

        GameFrame.Cameras.Instance.enableUGUICamera = false;
        yield return null;
    }
    void Update() {
        if (Nets.Instance != null)
            Nets.Instance.Update();
    }

    void OnDestroy() {
        this.game_.Quit();
    }
}

