using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class FSMState {
    public GameProcessState processState {
        get {
            return mProcessState;
        }
    }
    public TargetState state {
        get {
            return mHeroState;
        }
    }

    public Condtion completeCondtion;
    public Condtion interruptCondtion;
    public List<Transition> transitions;

    protected TargetState mHeroState;
    protected GameProcessState mProcessState = GameProcessState.None;

    public void Enter() {
    }
    public void Exit() {
    }
    public void Init() {
    }

    public FSMState CheckTransition() {
        throw new Exception();
    }

    public virtual bool Start() {
        return false;
    }

    public virtual void Update() {
        if (completeCondtion.True()) {
            mProcessState = GameProcessState.Completed;
            return;
        }
        if (interruptCondtion != null) {
            if(interruptCondtion.True()) {
                mProcessState = GameProcessState.Sleeping;
            }
        }
    }

    public virtual void Sleep() {
    }

    public virtual bool Resume() {
        return false;
    }
}
