using FairyGUI;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace AppCore
{

public class UIController: BaseController
{
    public static UIController Instance
    {
        set;
        get;
    }

    public ProgressView currentProgressView;

    public Dictionary<string, ViewBase> mViews = new Dictionary<string, ViewBase>();


    public T Show<T>(bool only = true) where T : ViewBase, new()
    {
        T ret = Get<T>();
        if(ret != null)
        {
            if (only)
            {
                foreach (var view in mViews)
                    view.Value.Hide();
                GRoot.inst.CloseAllWindows();
            }
            ret.Show();
        }
        return ret;
    }

    public void Close()
    {
        foreach (var view in mViews)
            view.Value.Hide();
        GRoot.inst.CloseAllWindows();
    }


    public T Hide<T>() where T : ViewBase, new()
    {
        return default(T);
    }

    public T Get<T>() where T : ViewBase, new()
    {
        ViewBase ret;
        string name = typeof(T).Name;
        if (!mViews.TryGetValue(name, out ret))
        {
            ret = LoadView<T>(name);
            if(ret != null)
            {
                mViews.Add(name, ret);
            }
        }
        if (ret != null)
            return (T)ret;
        else
            return null;
    }

    public T LoadView<T>(string name) where T : ViewBase, new ()
    {
        var sceneObject = Loader.Instance.Create<GameObject>("GUI/" + name);
        if (!sceneObject)
        {
            Debug.LogError("Error Path:" + "GUI" + name);
            return null;
        }
        sceneObject.name = name;
        var panel = sceneObject.GetComponent<UIPanel>();
        if (panel == null)
            return null;
        T ret = new T();
        ret.panel = panel;
        GRoot.inst.AddChild(ret);
        return ret;
    }

    public override IEnumerator initialize()
    {
        GRoot.inst.SetContentScaleFactor(576, 1024);
        UIPackage.AddPackage("UI/Basics");
        yield return null;
    }


    public override IEnumerator onGameStageClose()
    {
        throw new NotImplementedException();
    }
}
}
