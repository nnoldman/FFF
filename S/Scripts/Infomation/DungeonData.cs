using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public enum DungeonType
{
    None,
    Daily,
    War,
}
public enum DugenonDefine
{
    Normal,     //普通
    Elite,      //精英
}
namespace GameData
{
    /// <summary>
    /// 副本通用配置
    /// </summary>
    public class DungeonData : GameData<DungeonData>
    {
        static public readonly string fileName = "xml/DungeonData";
        public string name;
        public int preID;
        public int star;
        public DungeonType type;
        public DugenonDefine define;
        public int icon;
        public int desc;
        public int times;

        public string descString
        {
            get
            {
                return Localization.Get(desc);
            }
        }

        public bool opened
        {
            get
            {
                if (preID == 0)
                    return true;
                else if (Informations.Instance.dungeons.ContainsKey(preID))
                    return Informations.Instance.dungeons[preID].occupy;
                return false;
            }
        }
        public string defineString
        {
            get
            {
                int text = 0;
                switch (define)
                {
                    case DugenonDefine.Normal:
                        text = 10673;
                        break;
                    case DugenonDefine.Elite:
                        text = 10674;
                        break;
                }
                return Localization.Get(text);
            }
        }
        public string stateString
        {
            get
            {
                if(opened)
                    return Localization.Get(10681);
                return Localization.Get(10680);
            }
        }
        public string texture
        {
            get
            {
                IconData iconData = IconData.Get(icon);
                if (iconData)
                    return iconData.texture;
                return null;
            }
        }
    }
} 
