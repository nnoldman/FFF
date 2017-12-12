using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {
public class DownloadFilesProcedure: Procedure {
    public Func<List<URLFile>> getURLs;
    public Action<WWW> contentHandler;
    private string error = string.Empty;

    public override IEnumerator Start() {
        var urls = getURLs();

        for(int i = 0; i < urls.Count; ++i) {
            var urlFile = urls[i];

            Debug.LogWarning("URL:" + urlFile);
            var request = new WWW(urlFile.url);

            yield return request;
            if (!string.IsNullOrEmpty(request.error)) {
                error = urlFile.url + request.error;
                Debug.LogWarning("DownloadFilesProcedure error:" + error);
                this.Wait();
            } else {
                if (contentHandler != null)
                    contentHandler(request);
            }
        }
    }

    protected override void OnWait() {
        MessageBoxParam param = new MessageBoxParam();
        param.rightButtonText = FrameOption.Texts.retry;
        param.leftButtonText = FrameOption.Texts.exit;
        param.content = FrameOption.Texts.updateResourceError;
        param.leftButtonCallback = (args) => Application.Quit();
        param.rightButtonCallback = (args) => state_ = ProduceState.Retry;
        Executer.ShowBox(param);
    }


}
}
