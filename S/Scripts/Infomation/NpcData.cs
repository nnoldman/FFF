using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum NpcType
{
    None,
    Soldier,
    General,
}

namespace GameData
{
    public class NpcData : GameData<NpcData>
    {
        //static public readonly string fileName = "xml/NpcData";
        public NpcType type;
        public string prefabName;
    }
}

