using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AppCore {
public enum AppState {
    None,
    BeginStart,
    CheckNet,
    CheckVersion,
    Updata,
    EndStart,
    ReadyToLogin,
    Logining,
    Playing,
    LoadingMap,
    ReadyToExit,
}
}
