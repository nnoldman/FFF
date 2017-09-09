using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public class SkillProperty
{
    public float damage;    ///伤害
    public float range;     ///范围
    public int cdTime;      ///毫秒
    public int percent;     ///触发几率
    public double cdTimeSecond
    {
        get
        {
            return cdTime * 0.001;
        }
    }
}

namespace GameData
{
    public class SkillData : GameData<SkillData>
    {
        static public readonly string fileName = "xml/SkillData";

        public SkillType type;
        public string name;
        public string typename;
        public int desc;
        public int icon;
        public string prefab;

        public List<SkillProperty> props;


        public string texture
        {
            get
            {
                return IconData.Get(icon).texture;
            }
        }
        public string prefabObj
        {
            get
            {
                return prefab;
            }
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
public enum SkillType
{
    Buff,       ///buff类型技能
    Passive,    ///被动触发技能
    Active,     ///主动技能
    Count,
}