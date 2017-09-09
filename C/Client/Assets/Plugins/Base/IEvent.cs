using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public interface IEventSender {
    void Trigger(int id, object data);
}

public interface IEventReceiver {
    void Bind(int id, Action callback);
    void Remove(int id);
    void RemoveAll();
}

public interface IComandReceiver {
    void OnPackage(int id, object data);
}

public delegate void GameEventHandler();
public delegate void GameEventHandler<T1>(T1 arg1);
public delegate void GameEventHandler<T1, T2>(T1 arg1, T2 arg2);
public delegate void GameEventHandler<T1, T2, T3>(T1 arg1, T2 arg2, T3 arg3);
public delegate IEnumerator YieldEventHandler();
