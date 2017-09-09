using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class LoadingTip : GameData<LoadingTip>
    {
        static public readonly string fileName = "xml/LoadingTip";
        public string tip;
    }
}
