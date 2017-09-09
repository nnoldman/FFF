using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace GameData
{
    public enum PropertyType
    {
        Attack,
        Defense,
        HP,
        Speed,
        AttackRange,
        Count,
    }

    public class Property
    {
        public int attack;
        public int defence;
        public int hp;
        public int speed;
        public int attackRange;
    }
    public class PropertyOfGeneral : Property
    {
        public int strength;
        public int intellect;
        public int captain;
        public int capacity;        ///带兵数量
    }
    public class PropertyLvOfSoldier
    {
        public int lv;
        public Property props;
    }
    public class PropertyRes
    {
        public string value;
        public bool valid;

        public static implicit operator bool(PropertyRes res)
        {
            if (res == null)
                return false;
            return res.valid;
        }
    }
    public class PropertyHelper
    {
        public string text { get; protected set; }
        public PropertyType type { get; protected set; }
        public int value;
        static string _appreciationFormat = Localization.Get(130);
        static string _curFormat = Localization.Get(131);

        public static PropertyRes GetAppreciationString(Property cur, Property next, PropertyType type)
        {
            PropertyRes res = new PropertyRes();
            int d0 = 0, d1 = 0;
            switch (type)
            {
                case PropertyType.Attack:
                    {
                        d0 = cur.attack;
                        if (next != null)
                            d1 = next.attack;
                    }
                    break;
                case PropertyType.AttackRange:
                    {
                        d0 = cur.attackRange;
                        if (next != null)
                            d1 = next.attackRange;
                    }
                    break;
                case PropertyType.Defense:
                    {
                        d0 = cur.defence;
                        if (next != null)
                            d1 = next.defence;
                    }
                    break;
                case PropertyType.HP:
                    {
                        d0 = cur.hp;
                        if (next != null)
                            d1 = next.hp;
                    }
                    break;
                case PropertyType.Speed:
                    {
                        d0 = cur.speed;
                        if (next != null)
                            d1 = next.speed;
                    }
                    break;
            }
            if (d0 > 0 && d1 == 0)
            {
                res.value = string.Format(_curFormat, Localization.Get((int)type + 110), d0);
                res.valid = true;
            }
            else if (d0 > 0 && d1 > 0)
            {
                res.value = string.Format(_appreciationFormat, Localization.Get((int)type + 110), d0, d1 - d0);
                res.valid = true;
            }
            return res;
        }
        public static PropertyHelper MakeProperty(PropertyType type, int value)
        {
            PropertyHelper p = new PropertyHelper();
            p.type = type;
            p.value = value;
            p.text = Localization.Get((int)type + 110);
            return p;
        }
    }
}


