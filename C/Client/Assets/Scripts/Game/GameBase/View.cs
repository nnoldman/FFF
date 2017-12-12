using Frame;
using GameFrame;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class View : ViewBase, Frame.IEventReceiver {

    protected override void RemoveEvents() {
    }

    void IEventReceiver.Bind(int id, Action callback) {
        throw new NotImplementedException();
    }

    void IEventReceiver.Remove(int id) {
        throw new NotImplementedException();
    }

    void IEventReceiver.RemoveAll() {
        throw new NotImplementedException();
    }
}
