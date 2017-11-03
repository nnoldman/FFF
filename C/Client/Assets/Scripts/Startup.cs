using UnityEngine;
using System.Collections;
using AppCore;
using FairyGUI;
using System.Reflection;
using System;
using System.Collections.Generic;

public class Startup : MonoBehaviour
{
    Startup mInstance;
    Game game_ = new Game();

    void Awake()
    {
        Debug.Assert(mInstance == null);
        mInstance = this;

        GateUIInterfaceProcedure.progressBar.Show();
        Flow.Instance.onProcess += GateUIInterfaceProcedure.progressBar.SetProgress;
        Flow.Instance.onTip += GateUIInterfaceProcedure.progressBar.SetText;

        Flow.Instance.Clear();
        Flow.Instance.AddProcedure<GateUIInterfaceProcedure>();
        Flow.Instance.AddProcedure<NetProcedure>();
        Flow.Instance.AddProcedure<VersionProcedure>();
        Flow.Instance.AddProcedure<ResourceProcedure>();
        Flow.Instance.AddProcedure<ConfigProcedure>();
        Flow.Instance.AddProcedure<PreloadProcedure>();
        Flow.Instance.AddProcedure<GameSystemsProcedure>();
        Flow.Instance.AddProcedure<LoginProcedure>();
        Flow.Instance.onStartEnd += OnStartEnd;

        StartCoroutine(Flow.Instance.Start());
    }

    IEnumerator OnStartEnd()
    {
        this.game_.AddController<Nets>();
        this.game_.AddController<UIController>();
        this.game_.AddController<GameFrame.Cameras>();
        yield return this.game_.Start();
        UIController.Instance.Show<HomePageWindow>();
        GateUIInterfaceProcedure.progressBar.Hide();
        GameFrame.Cameras.Instance.enableUGUICamera = false;
        yield return null;
    }
    void Update()
    {
        if (Nets.Instance != null)
            Nets.Instance.Update();
    }

    void OnDestroy()
    {
    }
}

