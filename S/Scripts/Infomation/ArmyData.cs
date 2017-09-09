/*----------------------------------------------------------------
// 模块名：IconData
// 模块描述：
//----------------------------------------------------------------*/

using System.Collections;
using System.Collections.Generic;
using System;

namespace GameData
{
    public class UpdegreeInfo
    {
        public int name;
        public string icon;
        public int leadCondtion;
        public int levelCondtion;
        public int cost;
        public string prefab;
        public Data.ItemCount needMetrials;
        public int skill;

        public string nameString
        {
            get
            {
                return Localization.Get(name);
            }
        }
        public string texture
        {
            get
            {
                return "icon/soldier/" + icon;
            }
        }

        public string getPrefabString(bool left)
        {
            return left ? (prefab + "_l") : (prefab + "_r");
        }
    }
    public class ArmyData : GameData<ArmyData>
    {
        static public readonly string fileName = "xml/ArmyData";

        public int name;
        public int alias;

        /// <summary>
        /// 克制的兵种
        /// </summary>
        public int quellType;
        public List<UpdegreeInfo> updegreeInfos;
        public List<int> source;

        public int commonAttack;
        public int commonDefence;
        public int commonHP;
        public int commonSpeed;
        public int desc;

        public ArmyData GetQuellType()
        {
            foreach (var v in dataMap)
            {
                if (v.Value.quellType == id)
                    return v.Value;
            }
            return null;
        }
        public ArmyData GetBeQuelledType()
        {
            return dataMap[quellType];
        }
        public static ArmyData Get(SoliderType type)
        {
            return Get((int)type);
        }
        public string descString
        {
            get
            {
                return Localization.Get(desc);
            }
        }
    }
}
