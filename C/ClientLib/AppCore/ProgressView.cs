using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AppCore {
public class ProgressView: View {
    public float progress {
        get {
            return mProgress;
        }
        set {
            mProgress = value;
        }
    }
    protected float mProgress;
}
}
