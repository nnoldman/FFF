using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class Param
    {
        public string name;
        public string display;
        public string defaultValue;
    }
    public class GMData:GameData<GMData>
    {
        static public readonly string fileName = "xml/GMData";
        public string name;
        public string display;
        public string desc;
        public List<Param> paramList;
    }
}
