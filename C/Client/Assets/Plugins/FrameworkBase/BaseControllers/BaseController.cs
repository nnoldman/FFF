using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public abstract class BaseController
{
    public virtual IEnumerator onGameStageClose()
    {
        yield return null;
    }
    public virtual void ForceClose()
    {
    }
    public abstract IEnumerator Initialize();
    public virtual void OnMapReady()
    {
    }
    public virtual void Update()
    {
    }
}
public abstract class GameController<T>: BaseController
{
    public static T Instance;
    //{
    //    get
    //    {
    //        return ms_instance;
    //    }
    //}
    //protected static T ms_instance;
}