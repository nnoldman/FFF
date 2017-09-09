using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Condtion {
    protected List<Condtion> mAndCondtions = new List<Condtion>();
    protected List<Condtion> mOrCondtions = new List<Condtion>();

    public bool True() {
        bool ret = AndCondtionTrue() && (ThisTrue() || OrCondtionTrue());
        return ret;
    }
    bool OrCondtionTrue() {
        for (int i = 0; i < mOrCondtions.Count; ++i) {
            if (mOrCondtions[i].True()) {
                return true;
            }
        }
        return false;
    }
    bool AndCondtionTrue() {
        for (int i = 0; i < mAndCondtions.Count; ++i) {
            if (!mAndCondtions[i].True()) {
                return false;
            }
        }
        return false;
    }
    protected virtual bool ThisTrue() {
        throw new Exception();
    }
    public Condtion And(Condtion rhs) {
        mAndCondtions.Add(rhs);
        return this;
    }

    public Condtion Or(Condtion rhs) {
        mOrCondtions.Add(rhs);
        return this;
    }
}
