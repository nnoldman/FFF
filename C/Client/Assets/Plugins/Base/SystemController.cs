using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public abstract class GameController {
    public abstract IEnumerator Initialize();
    public abstract void Update();
    public virtual void OnDestroy() { }
    public virtual void FixedUpdate() { }
    public virtual void LateUpdate() { }
    public virtual void OnSceneClose() { }
    public virtual void OnSceneOpen() { }
    public virtual void OnMapReady() { }
    public virtual void OnEnterGame() { }
    public virtual void OnExitGame() { }

    public string GetName() {
        return this.GetType().Name;
    }
}
