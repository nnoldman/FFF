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
    void Awake()
    {
        if (mInstance)
            return;
        mInstance = this;
        var flow = Flow.Instance;
        flow.onStartEnd += OnStartEnd;
        flow.checkNet += CheckNet;
        StartCoroutine(Flow.Instance.Restart());
    }

    IEnumerator OnStartEnd()
    {
        CSVParser.loader = LoadConfig;
        yield return LoadConfigs();
        yield return InitSystems();
        Nets.Instance = new Nets();
        yield return Nets.Instance.initialize();
        UIPackage.AddPackage("UI/Common");
        UIController.Instance.Show<HomePageWindow>();
        yield return null;
    }

    TextAsset LoadConfig(string name)
    {
#if UNITY_EDITOR
        return UnityEditor.AssetDatabase.LoadAssetAtPath<TextAsset>("Assets/Resources2/Config/" + name);
#endif
    }
    public void CheckNet()
    {
        switch(Application.internetReachability)
        {
        case NetworkReachability.NotReachable:
        {
            Flow.Instance.netState = NetState.Unreachable;
        }
        break;
        case NetworkReachability.ReachableViaLocalAreaNetwork:
        {
            Flow.Instance.netState = NetState.Local;
        }
        break;
        case NetworkReachability.ReachableViaCarrierDataNetwork:
        {
            Flow.Instance.netState = NetState.MobileNet;
        }
        break;
        }
    }
    public IEnumerator LoadConfigs()
    {
        Assembly asm = GetType().Assembly;
        var types = asm.GetTypes();
        List<Type> configTypes = new List<Type>();
        foreach (var type in types)
        {
            if (type.BaseType != null && type.BaseType.IsGenericType && type.BaseType.GetGenericTypeDefinition() == typeof(TableManager<>))
            {
                configTypes.Add(type);
            }
        }

        //Progress.Instance.Operator("加载配置中。。。", true);

        for (int i = 0; i < configTypes.Count; ++i)
        {
            var type = configTypes[i];
            var instance = Activator.CreateInstance(type);
            type.GetField("Instance", BindingFlags.Public | BindingFlags.Static).SetValue(null, instance);
            //Progress.Instance.Update(i + 1, configTypes.Count);
            yield return null;
        }
    }
    public IEnumerator InitSystems()
    {
        Assembly asm = GetType().Assembly;
        var types = asm.GetTypes();
        foreach (var type in types)
        {
            if (type.IsSubclassOf(typeof(SystemBase)))
            {
                var instance = Activator.CreateInstance(type);
                var filed = type.GetField("Instance", BindingFlags.Public | BindingFlags.Static);
                if (filed == null)
                {
                    Debug.LogError(string.Format("System {0} does not has Instance!"));
                }
                else
                {
                    filed.SetValue(null, instance);
                    var system = (SystemBase)instance;
                    if (system.timeConsuming)
                        yield return system.Initialize();
                }
            }
        }
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

