using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {

public enum ProduceError {
    NoError,
    CantFindProcedure,// 无法找到匹配state的步骤
    AllProcedureCantStart,// 所有步骤都启动失败
    ProduceExit,//步骤退出
}

public abstract class ServiceBase {
    public const int DefaultState = 0;
    public virtual string GetTipText() {
        return this.GetType().Name;
    }

    public void SetTargetState(int state) {
        targetState_ = state;
    }

    public ProduceError GetProduceError() {
        return produceError_;
    }

    public int GetErrorState() {
        return errorState_;
    }
    public virtual string GetStateDescription(int state) {
        return state.ToString();
    }
    public virtual void OnError(int state) {
    }

    public void AddProcedure(int fromState, int toState, Procedure produce) {
        produce.fromState = fromState;
        produce.toState = toState;
        if(procedures_.Find((it) => it.fromState == fromState && it.toState == toState) != null) {
            Debug.LogError(string.Format("Repeated Produce:{0}=>{1}", fromState, toState));
            return;
        }
        procedures_.Add(produce);
    }

    protected virtual IEnumerator OnStart() {
        yield return null;
    }

    public IEnumerator Start(int state) {
        this.procedures_.Clear();
        yield return this.OnStart();
        currentState_ = state;


        while (currentState_ != targetState_) {
            Debug.LogWarning(GetType().Name + " CurrentState :" + GetStateDescription(currentState_));
            var procedures = procedures_.FindAll((it) => it.fromState == currentState_);
            if(procedures == null || procedures.Count == 0) {
                errorState_ = currentState_;
                produceError_ = ProduceError.CantFindProcedure;
                yield break;
            }

            yield return ProcessProcedures(procedures);

            if(currentProduce_ == null) {
                produceError_ = ProduceError.AllProcedureCantStart;
                errorState_ = currentState_;
                yield break;
            }

            var produceState = currentProduce_.QueryState();

            while (produceState != ProduceState.NoError) {
                if(produceState == ProduceState.Error) {
                    produceError_ = ProduceError.ProduceExit;
                    errorState_ = currentState_;
                    yield break;
                } else if(produceState == ProduceState.Retry) {
                    yield return currentProduce_.Start();
                }
                produceState = currentProduce_.QueryState();
                yield return null;
            }
            if (currentProduce_.callback != null)
                currentProduce_.callback();
            currentState_ = currentProduce_.toState;
        }
        Debug.LogWarning(GetType().Name + " CurrentState :" + GetStateDescription(currentState_));
    }

    IEnumerator ProcessProcedures(List<Procedure> produces) {
        currentProduce_ = null;
        for (int i = 0; i < produces.Count; ++i) {
            var produce = produces[i];
            if (!produce.CanStart())
                continue;
            currentProduce_ = produce;
            break;
        }
        if (currentProduce_ != null)
            yield return currentProduce_.Start();
    }

    private int errorState_ = DefaultState;
    private ProduceError produceError_ = ProduceError.NoError;
    private List<Procedure> procedures_ = new List<Procedure>();
    private Procedure currentProduce_;
    private int targetState_ = DefaultState;
    private int currentState_ = DefaultState;
}

public class Service<T> : ServiceBase {
    public static T Instance;
}
}
