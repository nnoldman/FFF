using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public abstract class BaseController {
    public abstract IEnumerator onGameStageClose();
    public abstract IEnumerator initialize();
    public virtual void OnMapReady() {
    }
    public virtual void Update() {
    }
}
