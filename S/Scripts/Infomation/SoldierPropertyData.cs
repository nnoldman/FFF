using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class StarProperty
    {
        public int star;
        public List<Property> lvPropertys;
    }
    public class SoldierPropertyData : GameData<SoldierPropertyData>
    {
        static public readonly string fileName = "xml/SoldierPropertyData";

        public List<StarProperty> props;

        public static Property GetProperty(SoliderType type, int star, int lv)
        {
            return GetProperty((int)type, star, lv);
        }

        public static Property GetProperty(int type, int star, int lv)
        {
            try
            {
                SoldierPropertyData d = Get(type);
                if (d != null)
                {
                    StarProperty sp = d.props[star - 1];
                    if (sp != null)
                        return sp.lvPropertys[lv - 1];
                }
            }
            catch (Exception exc)
            {
                ALog.error(exc.Message);
            }

            return null;
        }
    }
}
