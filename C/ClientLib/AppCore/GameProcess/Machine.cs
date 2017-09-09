using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Machine {
    private List<Transition> mTransitions = new List<Transition>();
    private TargetState mCurrentTargetState = TargetState.Idle;

    public void UpdateStates() {
        for(int i = 0; i < mTransitions.Count; ++i) {
            var item = mTransitions[i];
            if(item.fromTo.from == mCurrentTargetState) {
                if(item.condtion.True()) {
                    OnLeaveState(mCurrentTargetState);
                    mCurrentTargetState = item.fromTo.to;
                    OnEnterState(mCurrentTargetState);
                    break;
                }
            }
        }
    }

    public void Initialize() {
        Transition[] trans = new Transition[] {
            new Transition(new FromTo(TargetState.Idle, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.Idle, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.Idle, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.Idle, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.Idle, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.Idle, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.Idle, TargetState.OperUI), new Condtion()),

            new Transition(new FromTo(TargetState.KeyMove, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.KeyMove, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.KeyMove, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.KeyMove, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.KeyMove, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.KeyMove, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.KeyMove, TargetState.OperUI), new Condtion()),

            new Transition(new FromTo(TargetState.PathFinding, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.PathFinding, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.PathFinding, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.PathFinding, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.PathFinding, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.PathFinding, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.PathFinding, TargetState.OperUI), new Condtion()),

            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.FightOneTarget, TargetState.OperUI), new Condtion()),

            new Transition(new FromTo(TargetState.AutoFight, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.AutoFight, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.AutoFight, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.AutoFight, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.AutoFight, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.AutoFight, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.AutoFight, TargetState.OperUI), new Condtion()),

            new Transition(new FromTo(TargetState.AutoTask, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.AutoTask, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.AutoTask, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.AutoTask, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.AutoTask, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.AutoTask, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.AutoTask, TargetState.OperUI), new Condtion()),

            new Transition(new FromTo(TargetState.OperUI, TargetState.Idle), new Condtion()),
            new Transition(new FromTo(TargetState.OperUI, TargetState.KeyMove), new Condtion()),
            new Transition(new FromTo(TargetState.OperUI, TargetState.PathFinding), new Condtion()),
            new Transition(new FromTo(TargetState.OperUI, TargetState.FightOneTarget), new Condtion()),
            new Transition(new FromTo(TargetState.OperUI, TargetState.AutoFight), new Condtion()),
            new Transition(new FromTo(TargetState.OperUI, TargetState.AutoTask), new Condtion()),
            new Transition(new FromTo(TargetState.OperUI, TargetState.OperUI), new Condtion()),
        };
    }

    public void OnLeaveState(TargetState state) {
    }

    public void OnEnterState(TargetState state) {
    }
}
