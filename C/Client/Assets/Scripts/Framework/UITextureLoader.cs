using UnityEngine;
using FairyGUI;
using System.IO;
using GameFrame;

/// <summary>
/// Extend the ability of GLoader
/// </summary>
public class UITextureLoader : GLoader {
    protected override void LoadExternal() {
        Icons.Instance.LoadIcon(this.url, OnLoadSuccess, OnLoadFail);
    }

    protected override void FreeExternal(NTexture texture) {
        texture.refCount--;
    }

    void OnLoadSuccess(NTexture texture) {
        if (string.IsNullOrEmpty(this.url))
            return;

        this.onExternalLoadSuccess(texture);
    }

    void OnLoadFail(string error) {
        Debug.Log("load " + this.url + " failed: " + error);
        this.onExternalLoadFailed();
    }
}
