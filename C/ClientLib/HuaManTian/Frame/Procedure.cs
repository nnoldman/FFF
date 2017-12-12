using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
public enum ProduceState {
    NoError,
    Running,
    Retry,
    Error,
}
public class Procedure {
    public int fromState;
    public int toState;
    public string name;
    /// <summary>
    ///if not null,it will call on start finish
    /// </summary>
    public Action callback;

    public Func<ProduceState> queryState;
    public Func<bool> canStart;
    public YieldEventHandler onStart;
    protected ProduceState state_ = ProduceState.NoError;

    public virtual ProduceState QueryState() {
        if (queryState != null)
            return queryState();
        return state_;
    }
    /// <summary>
    /// Start
    /// </summary>
    /// <returns></returns>
    public virtual IEnumerator Start() {
        if(onStart != null)
            yield return onStart();
    }

    public virtual bool CanStart() {
        if (canStart != null)
            return canStart();
        return true;
    }

    protected void Wait() {
        this.OnWait();
        state_ = ProduceState.Running;
    }
    protected virtual void OnWait() {
    }
}
}
