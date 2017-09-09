using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public abstract class IManager {
    public abstract bool Initialize();
    public abstract void Update();
    public virtual void OnDestroy() { }
    public virtual void FixedUpdate() { }
    public virtual void LateUpdate() { }
    public virtual void Start() { }
    public virtual void OnSceneClose() { }
    public virtual void OnSceneOpen() { }
    public virtual void OnMapLoaded() { }
    public virtual void OnEnterGame() { }
    public virtual void OnGameExit() { }

    public string GetName() {
        return this.GetType().Name;
    }
}
