using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class GateUIService :  Frame.Service<GateUIService> {
    protected override IEnumerator OnStart() {
        return base.OnStart();
    }

    public override string GetTipText() {
        return "加载内部资源";
    }
}
