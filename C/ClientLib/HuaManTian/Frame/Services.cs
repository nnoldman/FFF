using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

namespace Frame {
public class Services {
    public delegate void ProcessHandler(int cur, int max, string fmt);
    public delegate void TipHandler(string tip);
    public static Services Instance {
        get {
            if (mInstance == null)
                mInstance = new Services();
            return mInstance;
        }
    }
    public static Services mInstance;
    public ProcessHandler onProcess;
    public TipHandler onTip;
    private List<ServiceBase> services_ = new List<ServiceBase>();


    public void Clear() {
        services_.Clear();
    }

    public YieldEventHandler onStartEnd {
        get;
        set;
    }

    internal Services() {
    }

    public void AddService<T>()where T: ServiceBase {
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
                onProcess(i, services_.Count, "{0}/{1}");
            yield return service.Start(ServiceBase.DefaultState);
            var procedureError = service.GetProduceError();
            if (procedureError != ProduceError.NoError) {
                var errorState = service.GetErrorState();
                Debug.LogWarning(string.Format("ServiceError=>{0},state:{1},error:{2}"
                                               , service.GetType().Name
                                               , service.GetStateDescription(errorState),
                                               procedureError
                                              ));
                service.OnError(errorState);
                yield break;
            }
        }
        if (onProcess != null)
            onProcess(services_.Count, services_.Count, "{0}/{1}");
        if (onStartEnd != null)
            yield return onStartEnd();
    }
}
}
