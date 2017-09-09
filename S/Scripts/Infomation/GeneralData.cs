/*----------------------------------------------------------------
// 模块名：GeneralData
// 模块描述：武将配置
//----------------------------------------------------------------*/
using System.Collections;
using System.Collections.Generic;
using System;

namespace GameData
{
    public class GeneralData : GameData<GeneralData>
    {
        static public readonly string fileName = "xml/GeneralData";

        public static int MAX_STAR_COUNT = 5;
        public static int MAX_HEART_COUNT = 5;
        public static int MAX_INTIMACY = 100;
        public static int INTIMACY_SEG = MAX_INTIMACY / MAX_HEART_COUNT;

        public bool adviser;
        public string name;
        public string icon;
        public int star;
        public int speciality;      ///专长
        public int direction;       ///定位
        public SoliderType type;    ///兵种
        public string prefabName;
        public int desc;
        public int condtion;
        public List<int> sources;

        public List<PropertyOfGeneral> baseinfos;

        public GeneralData()
        {
        }
        public string description
        {
            get
            {
                return Localization.Get(desc);
            }
        }

        public string nameString
        {
            get
            {
                return name;
            }
        }
        public string nameStringWithColor
        {
            get
            {
                ColorString colorstring = new ColorString();
                colorstring.value = nameString;
                colorstring.color = QualityColorData.Get(star).color;
                return colorstring;
            }
        }
        public string nameStringWithColorVertical
        {
            get
            {
                string res = string.Empty;
                for (int i = 0; i < name.Length; ++i)
                {
                    res += name[i];
                    if (i == name.Length - 1)
                        break;
                    res += "\n";
                }

                ColorString colorstring = new ColorString();
                colorstring.value = res;
                colorstring.color = QualityColorData.Get(star).color;
                return colorstring;
            }
        }
        public string specialityString
        {
            get
            {
                return Localization.Get(speciality);
            }
        }

        public string directionString
        {
            get
            {
                return Localization.Get(direction);
            }
        }

        public string texture
        {

            get
            {
                return "icon/general/" + icon;
            }
        }

        public string GetPrefab(bool leftSide)
        {
            return leftSide ? prefabName + "_l" : prefabName + "_r";
        }
    }
}
