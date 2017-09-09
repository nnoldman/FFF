using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public struct FromTo {
    public TargetState from;
    public TargetState to;

    public FromTo(TargetState from, TargetState to) : this() {
        this.from = from;
        this.to = to;
    }
}
public struct Transition {
    public FromTo fromTo;
    public Condtion condtion;
    public Transition(FromTo fromTo, Condtion condtion) : this() {
        this.fromTo = fromTo;
        this.condtion = condtion;
    }
}