using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class GameEvents : Dispatcher {
    public static GameEvents Instance {
        get {
            if (smInstance == null) {
                smInstance = new GameEvents();
            }
            return smInstance;
        }
    }
    static GameEvents smInstance;

    public void Bind(GameEventID id, Action<object> callback) {
        Bind((int)id, callback);
    }

    public void Bind(GameEventID id, Action callback) {
        Bind((int)id, callback);
    }

    public void Trigger(GameEventID id, object args = null) {
        Trigger((int)id, args);
    }
}