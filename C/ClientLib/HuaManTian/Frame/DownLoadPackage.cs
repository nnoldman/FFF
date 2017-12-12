using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {
public class DownLoadPackage: Procedure {
    public string appSite;
    public override IEnumerator Start() {
        this.Wait();
        yield return null;
    }

    protected override void OnWait() {
        MessageBoxParam param = new MessageBoxParam();
        param.rightButtonText = FrameOption.Texts.goToDownload;
        param.leftButtonText = FrameOption.Texts.exit;
        param.content = FrameOption.Texts.downloadPackage;
        param.leftButtonCallback = (args) => Application.Quit();
        param.rightButtonCallback = (args) => Application.OpenURL(appSite);
        Executer.ShowBox(param);
    }
}
}
