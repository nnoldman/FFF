using UnityEngine;
using System.Collections;
using AppCore;
using FairyGUI;

public class Startup : MonoBehaviour {
    Startup mInstance;
    void Awake() {
        if (mInstance)
            return;
        mInstance = this;
        var flow = Flow.Instance;
        flow.onStartEnd += OnStartEnd;
        flow.checkNet += CheckNet;
        StartCoroutine(Flow.Instance.Restart());
    }

    IEnumerator OnStartEnd() {
        Nets.Instance = new Nets();
        yield return Nets.Instance.initialize();
        UIPackage.AddPackage("UI/Common");
        UIController.Instance.Show<HomePageWindow>();
        yield return null;
    }

    public void CheckNet() {
        switch(Application.internetReachability) {
        case NetworkReachability.NotReachable: {
            Flow.Instance.netState = NetState.Unreachable;
        }
        break;
        case NetworkReachability.ReachableViaLocalAreaNetwork: {
            Flow.Instance.netState = NetState.Local;
        }
        break;
        case NetworkReachability.ReachableViaCarrierDataNetwork: {
            Flow.Instance.netState = NetState.MobileNet;
        }
        break;
        }
    }

    void Update() {
        if (Nets.Instance != null)
            Nets.Instance.Update();
    }

    void OnDestroy() {
    }
}

