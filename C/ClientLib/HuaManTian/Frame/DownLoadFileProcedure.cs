using System;
using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace Frame {

public class DownLoadFileProcedure: Procedure {
    public Func<string> getURL;
    public Action<WWW> contentHandler;
    private string error = string.Empty;
    private int errorWhenTryTimes = 1;

    public override IEnumerator Start() {
        string url = getURL();
        Debug.LogWarning("URL:" + url);
        var request = new WWW(url);
        yield return request;
        if(!string.IsNullOrEmpty(request.error)) {
            error = getURL() + request.error;
            this.Wait();
        } else {
            if (contentHandler != null)
                contentHandler(request);
        }
    }

    protected override void OnWait() {
        MessageBoxParam param = new MessageBoxParam();
        param.rightButtonText = FrameOption.Texts.retry;
        param.leftButtonText = FrameOption.Texts.goToSetting;
        param.content = error;
        param.leftButtonCallback = (args) => Application.Quit();
        param.rightButtonCallback = (args) => state_ = ProduceState.Retry;
        Executer.ShowBox(param);
    }
}
}

