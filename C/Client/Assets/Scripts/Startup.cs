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

        GateUIService.progressBar.Show();
        Flow.Instance.onProcess += GateUIService.progressBar.SetProgress;
        Flow.Instance.onTip += GateUIService.progressBar.SetText;

        Flow.Instance.Clear();
        Flow.Instance.AddService<GateUIService>();
        Flow.Instance.AddService<NetService>();
        Flow.Instance.AddService<VersionService>();
        Flow.Instance.AddService<ResourceService>();
        Flow.Instance.AddService<ConfigService>();
        Flow.Instance.AddService<PreloadService>();
        Flow.Instance.AddService<GameSystemsServie>();
        Flow.Instance.AddService<LoginService>();
        Flow.Instance.onStartEnd += OnStartEnd;

        StartCoroutine(Flow.Instance.Start());
    }

    IEnumerator OnStartEnd() {
        this.game_.AddController<Nets>();
        this.game_.AddController<GameFrame.Icons>();
        this.game_.AddController<UIs>();
        this.game_.AddController<GameFrame.Cameras>();
        yield return this.game_.Start();
        UIs.Instance.Show<HomePageWindow>();
        GateUIService.progressBar.Hide();
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

