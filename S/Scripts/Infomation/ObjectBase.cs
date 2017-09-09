using Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class ObjectBase : GameData<ObjectBase>
    {
        static public readonly string fileName = "xml/ObjectBase";

        public int icon;
        public string name;
        public int quality;
        public int itemType;
        public int cap;
        public int desc;
        public string props;
        public int price;


        public string description
        {
            get
            {
                return Localization.Get(desc);
            }
        }
        public string nameWithColor
        {
            get
            {
                return Fun.ParseColor_NGUIRGB(qualityColor) + name + "[-]";
            }
        }
        public Color qualityColor
        {
            get
            {
                return QualityColorData.Get(quality).color;
            }
        }
        public string texture
        {
            get
            {
                return IconData.Get(icon).texture;
            }
        }
        public ItemType type
        {
            get
            {
                return (ItemType)itemType;
            }
        }
        public static ObjectBase Get(uint id)
        {
            return Get((int)id);
        }
    }
}
