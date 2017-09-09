using AppCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class View : ViewBase, IEventReceiver
{
    void IEventReceiver.Bind(int id, Action callback)
    {
        throw new NotImplementedException();
    }

    void IEventReceiver.Remove(int id)
    {
        throw new NotImplementedException();
    }

    void IEventReceiver.RemoveAll()
    {
        throw new NotImplementedException();
    }

    public void Bind(int id, Action callback)
    {
        throw new Exception("The method or operation is not implemented.");
    }

    public void Remove(int id)
    {
        throw new Exception("The method or operation is not implemented.");
    }

    public void RemoveAll()
    {
        throw new Exception("The method or operation is not implemented.");
    }

    protected override void RemoveEvents()
    {
    }
}
