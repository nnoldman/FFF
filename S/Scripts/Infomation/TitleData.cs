using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class TitleData:GameData<TitleData>
    {
        static public readonly string fileName = "xml/TitleData";
        public int name;
        public Property addProp;

        public string titleString
        {
            get
            {
                return Localization.Get(name);
            }
        }
    }
}

