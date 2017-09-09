using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class PropertyLvOfEquip:Property
    {
        public int cost;        ///升级花费
    }
    public class EquipData : GameData<EquipData>
    {
        static public readonly string fileName = "xml/EquipData";
        public int next;
        public Data.ItemCount cost;
        public int copperCost;
        public List<PropertyLvOfEquip> lvPropertys;

        public int GetCost(int curlv, int tarLv)
        {
            if (curlv >= tarLv)
                return 0;
            if (curlv >= lvPropertys.Count)
                return 0;
            if (tarLv >= lvPropertys.Count)
                return 0;
            int sum = 0;
            for (int i = curlv - 1; i < tarLv - 1; ++i)
            {
                sum += lvPropertys[i].cost;
            }
            return sum;
        }
        public bool IsMax(int lv)
        {
            return lv == maxLv;
        }
        public int maxLv
        {
            get
            {
                return lvPropertys.Count;
            }
        }
    }
}