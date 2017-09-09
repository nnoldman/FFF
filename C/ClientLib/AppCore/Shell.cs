using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AppCore {
public class Shell {
    public Configuration config {
        get {
            return mConfig;
        }
        set {
            mConfig = value;
        }
    }

    public App app {
        get {
            return mApp;
        }
    }
    public ProgressView updataView;

    public AppState state {
        get {
            return mAppState;
        }
        internal set {
            mAppState = value;
        }
    }

    private App mApp;
    private Configuration mConfig = new Configuration();
    private AppState mAppState = AppState.None;

    public IEnumerator RestartApp() {
        bool updata = false;
        if(mApp != null) {
            mApp.Close();
            mApp = null;
        } else {
            updata = true;
        }
        yield return null;
        mApp = new App();
        if(updata) {
            app.CheckNet();
            yield return null;
            app.CheckVersion();
            yield return null;
        }
        app.Start();
        yield return null;
    }

    public void Close() {
    }
}
}
