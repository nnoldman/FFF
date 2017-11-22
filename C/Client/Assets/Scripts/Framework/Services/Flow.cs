using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

namespace GameFrame {
public class Flow {
    public delegate void ProcessDelegate(int cur, int max);
    public delegate void Tip(string tip);
    public static Flow Instance {
        get {
            if (mInstance == null)
                mInstance = new Flow();
            return mInstance;
        }
    }
    public static Flow mInstance;
    public ProcessDelegate onProcess;
    public Tip onTip;
    private List<GameFrame.ServiceBase> services_ = new List<GameFrame.ServiceBase>();


    public void Clear() {
        services_.Clear();
    }

    public YieldEventHandler onStartEnd {
        get;
        set;
    }

    internal Flow() {
    }

    public void AddService<T>()where T: GameFrame.ServiceBase {
        var type = typeof(T);
        var creator = type.BaseType.GetField("Instance");
        var instance = Activator.CreateInstance<T>();
        creator.SetValue(null, instance);
        services_.Add(instance);
    }

    public IEnumerator Start() {
        for(int i = 0; i < services_.Count; ++i) {
            var service = services_[i];
            if (onTip != null)
                onTip(service.GetTipText());
            if (onProcess != null)
                onProcess(i, services_.Count);
            yield return service.Start();
            if (service.error)
                yield break;
        }

        if (onProcess != null)
            onProcess(services_.Count, services_.Count);

        if (onStartEnd != null)
            yield return onStartEnd();
    }
}
}
