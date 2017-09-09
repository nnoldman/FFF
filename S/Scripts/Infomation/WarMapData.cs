using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class WarMapData : GameData<WarMapData>
    {
        static public readonly string fileName = "xml/WarMapData";
        public List<int> chapters ;
    }
}
