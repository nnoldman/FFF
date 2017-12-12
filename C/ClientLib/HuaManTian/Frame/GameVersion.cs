using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
[Serializable]
public class GameVersion : IBoolObject {
    public int main = 0;
    public int program = 0;
    public int resource = 0;
    public string time;

    public bool ProgramHigherThan(GameVersion b) {
        if (b == null)
            return true;
        if (this.main > b.main)
            return true;
        if (this.main == b.main && this.program > b.program)
            return true;
        return false;
    }

    public bool ResourceHigherThan(GameVersion b) {
        if (ProgramHigherThan(b))
            return true;
        if (this.main >= b.main && this.program >= b.program && this.resource > b.resource)
            return true;
        return false;
    }

    public bool HigherThan(GameVersion b) {
        if (ProgramHigherThan(b))
            return true;
        return ResourceHigherThan(b);
    }

    public override string ToString() {
        return string.Format("{0}.{1}.{2}", main, program, resource);
    }
    public static GameVersion Parse(string content) {
        GameVersion version = new GameVersion();
        try {
            var strs = content.Split(new char[1] { '.' });
            if (strs.Length > 0)
                version.main = int.Parse(strs[0]);
            if (strs.Length > 1)
                version.program = int.Parse(strs[1]);
            if (strs.Length > 2)
                version.resource = int.Parse(strs[2]);
        } catch (Exception exc) {
            UnityEngine.Debug.LogWarning(exc.Message);
        }
        return version;
    }

    public bool Equals(GameVersion rhs) {
        return this.main == rhs.main && this.program == rhs.program && this.resource == rhs.resource;
    }
}
}
