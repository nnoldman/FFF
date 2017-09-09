using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AppCore {

public class UIManager: IManager {
    public static UIManager Instance {
        internal set;
        get;
    }

    public ProgressView currentProgressView;

    public void Show<T>() where T : View {
    }

    public void Hide<T>() where T : View {
    }

    public T Get<T>() where T : View {
        return default(T);
    }

    public override bool Initialize() {
        throw new Exception("The method or operation is not implemented.");
    }

    public override void Update() {
        throw new Exception("The method or operation is not implemented.");
    }
}
}
