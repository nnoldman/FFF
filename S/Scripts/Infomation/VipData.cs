using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class VipData:GameData<VipData>
    {
        static public readonly string fileName = "xml/Vip";
        public uint allCharge;          ///充值金额
        public int right;               ///权利说明

        public string rightString
        {
            get
            {
                return Localization.Get(right);
            }
        }

        public static int maxLv
        {
            get
            {
                return dataMap.Count;
            }
        }

        public static int CalVip(uint charge)
        {
            foreach (var v in dataMap)
            {
                if (charge < v.Value.allCharge)
                {
                    return v.Key - 1;
                }
            }
            return dataMap.Count;
        }

        public static string GetVipSpriteString(int vip)
        {
            return "V" + vip.ToString();
        }
    }
}
