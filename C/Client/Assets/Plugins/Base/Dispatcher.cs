using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Dispatcher {
    public Dictionary < int, List<Action<object>>> mListeners1 = new Dictionary<int, List<Action<object>>>();
    public Dictionary<int, List<Action>> mListeners = new Dictionary<int, List<Action>>();

    public void Bind(int id, Action<object> callback) {
        List<Action<object>> rets;
        if(!mListeners1.TryGetValue(id, out rets)) {
            rets = new List<Action<object>>();
            mListeners1.Add(id, rets);
        }
        if(!rets.Contains(callback))
            rets.Add(callback);
    }

    public void Bind(int id, Action callback) {
        List<Action> rets;
        if (!mListeners.TryGetValue(id, out rets)) {
            rets = new List<Action>();
            mListeners.Add(id, rets);
        }
        if(!rets.Contains(callback))
            rets.Add(callback);
    }

    public void Trigger(int id, object args) {
        {
            List<Action<object>> rets;
            if (mListeners1.TryGetValue(id, out rets)) {
                for (int i = 0; i < rets.Count; ++i) {
                    rets[i].Invoke(args);
                }
            }
        }
        {
            List<Action> rets;
            if (mListeners.TryGetValue(id, out rets)) {
                for (int i = 0; i < rets.Count; ++i) {
                    rets[i].Invoke();
                }
            }
        }
    }

    public void RemoveListener(object instance) {
        foreach(var listeners in mListeners) {
            listeners.Value.RemoveAll((item) => item.Target == instance);
        }

        foreach (var listeners in mListeners1) {
            listeners.Value.RemoveAll((item) => item.Target == instance);
        }
    }
}
