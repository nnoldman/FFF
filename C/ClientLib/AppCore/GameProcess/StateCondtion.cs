using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class StateCondtion: Condtion {
    public TargetState from;
    public TargetState to;
    public bool Right() {
        return false;
    }
}
