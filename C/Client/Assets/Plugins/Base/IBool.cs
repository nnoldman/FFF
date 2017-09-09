using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public  class IBool {
    public static implicit operator bool(IBool b) {
        return b != null;
    }
}
