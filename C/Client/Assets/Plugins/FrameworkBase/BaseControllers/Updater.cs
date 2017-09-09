using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Updater: BaseController {

    public enum UpdataState {
        None,
        Error,
        Resource,
        Program,
        Unompress,
        Success,
    }

    public static Updater Instance {
        set;
        get;
    }

    public UpdataState state {
        get;
        set;
    }


    public override IEnumerator initialize() {
        yield return null;
    }

    public IEnumerator CheckUpdata() {
        while (state != UpdataState.Success) {
            switch(state) {
            case UpdataState.None:
                yield return Start();
                break;
            case UpdataState.Resource:
                yield return UpdataResource();
                break;
            case UpdataState.Program:
                yield return UpdateProgram();
                break;
            case UpdataState.Unompress:
                yield return Uncompress();
                break;
            case UpdataState.Error:
                yield return ProcessError();
                break;
            }
            yield return 0;
        }
    }
    public IEnumerator Start() {
        state = UpdataState.Success;
        yield return 0;
    }

    public IEnumerator UpdateProgram() {
        yield return 0;
    }
    public IEnumerator UpdataResource() {
        yield return 0;
    }
    public IEnumerator Uncompress() {
        yield return 0;
    }
    public IEnumerator ProcessError() {
        yield return 0;
    }

    public override void Update() {
    }

    public override IEnumerator onGameStageClose() {
        yield return null;
    }
}
