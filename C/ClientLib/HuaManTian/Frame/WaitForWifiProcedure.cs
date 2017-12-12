using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {
public class WaitForWifiProcedure: Procedure {
    private float startTime_;
    /// <summary>
    /// 开始检测网络
    /// </summary>
    /// <returns></returns>
    public override IEnumerator Start() {
        startTime_ = Time.realtimeSinceStartup;
        while (state_ != ProduceState.Error && Application.internetReachability != NetworkReachability.ReachableViaLocalAreaNetwork) {
            if (Time.realtimeSinceStartup - startTime_ > FrameOption.Base.checkWifiReachedSeconds) {
                this.Wait();
            }
            yield return null;
        }
    }

    protected override void OnWait() {
        MessageBoxParam param = new MessageBoxParam();
        param.rightButtonText = FrameOption.Texts.goToOpenWifi;
        param.leftButtonText = FrameOption.Texts.continueDownload;
        param.content = FrameOption.Texts.downloadWarning;
        param.leftButtonCallback = (args) => {
            FrameOption.Base.allowDownloadWithoutWifi = true;
            state_ = ProduceState.NoError;
        };

        param.rightButtonCallback = (args) => Application.Quit();
        Executer.ShowBox(param);
    }
}
}
