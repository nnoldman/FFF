using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AppCore {
public class App {
    private SceneParam mSceneParam;

    public bool CheckNet() {
        return true;
    }

    public bool CheckVersion() {
        return true;
    }

    public void Start() {
        UIManager.Instance = new UIManager();
    }

    public IEnumerator LoadScene(SceneParam param) {
        mSceneParam = param;
        OnSceneClose();
        yield return null;
        yield return null;
        OnSceneOpen();
        yield return null;
    }

    public void Close() {
    }
    public void OnSceneOpen() {
    }
    public void OnSceneClose() {
    }
    public void OnMapLoaded() {
    }
    public void OnHeroReady() {
    }
}
}
