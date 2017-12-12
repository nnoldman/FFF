using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {
public class WaitForNetProcedure: Procedure {
    private float startTime_;
    /// <summary>
    /// 开始检测网络
    /// </summary>
    /// <returns></returns>
    public override IEnumerator Start() {
        startTime_ = Time.realtimeSinceStartup;
        while (state_ != ProduceState.Error && Application.internetReachability == NetworkReachability.NotReachable) {
            if (Time.realtimeSinceStartup - startTime_ > FrameOption.Base.checkNetReachedSeconds) {
                this.Wait();
            }
            yield return null;
        }
    }

    protected override void OnWait() {
        MessageBoxParam param = new MessageBoxParam();
        param.rightButtonText = FrameOption.Texts.retry;
        param.leftButtonText = FrameOption.Texts.goToSetting;
        param.content = FrameOption.Texts.netWarning;
        param.leftButtonCallback = (args) => Application.Quit();
        param.rightButtonCallback = (args) => state_ = ProduceState.Retry;
        Executer.ShowBox(param);
    }
}
}
