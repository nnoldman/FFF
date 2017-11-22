using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class GateUIService :  GameFrame.Service<GateUIService> {
    public static IProgressBar progressBar {
        get {
            if(currentProgressBar_ == null)
                currentProgressBar_ = GateWindow.Instance;
            return currentProgressBar_;
        }
        set {
            currentProgressBar_ = value;
        }
    }

    static IProgressBar currentProgressBar_;

    public override IEnumerator Start() {
        return base.Start();
    }

    public override string GetTipText() {
        return "加载内部资源";
    }
}
