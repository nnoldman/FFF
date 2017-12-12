using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {
public class DownloadRemoteRootOptionProcedure : Procedure {
    /// <summary>
    /// 默认尝试次数
    /// </summary>
    public int defalutTryTime = 3;
    public Func<string> getURL;
    public Action<WWW> contentHandler;
    private string error = string.Empty;

    private int tryTimes_ = 0;

    public override IEnumerator Start() {
        string url = getURL();
        Debug.LogWarning("URL:" + url);
        var request = new WWW(url);
        yield return request;
        if (!string.IsNullOrEmpty(request.error)) {
            error = getURL() + request.error;
            Debug.LogWarning(error);
            if(tryTimes_ < this.defalutTryTime) {
                state_ = ProduceState.Retry;
            }
            tryTimes_++;
            if(tryTimes_ == defalutTryTime) {
                if (Frame.FrameOption.Base.allowRunWithoutRemoteRootOption)
                    state_ = ProduceState.NoError;
                else
                    state_ = ProduceState.Error;
            }
        } else {
            if (contentHandler != null)
                contentHandler(request);
        }
    }
}
}
