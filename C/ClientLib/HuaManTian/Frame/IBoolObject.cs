using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
public class IBoolObject {
    public static implicit operator bool(IBoolObject obj) {
        return obj != null;
    }
}
}
