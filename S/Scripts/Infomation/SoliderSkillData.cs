using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class SoliderSkillData : GameData<SoliderSkillData>
    {
        static public readonly string fileName = "xml/SoliderSkillData";

        public SkillType type;
        public int icon;
        public string name;
        public string typename;
        public string desc;

        public string texture
        {
            get
            {
                return IconData.Get(icon).texture;
            }
        }
        public string descString
        {
            get
            {
                return desc;
            }
        }
    }
}