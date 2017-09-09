using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class GeneralTalk
{
    public int generalID = 0;
    public string content;
}

public enum FormationType
{
    Down = 0,
    Middle = 1,
    Up = 2
}

public enum FormationPos
{
    Front = 0,
    Centre = 1,
    Back = 2
}

namespace GameData
{

    public class DugenSoldier
    {
        public int lv;
        public int star;
    }
    public class GeneralPos
    {
        public int generalID;
        public int generalLv = 1;
        public FormationPos x;
        public FormationType y;
        public double waitTime;        //出战等待时间
        public List<DugenSoldier> soliders;
    }
    /// <summary>
    /// 征战副本
    /// </summary>
    public class DungeonWar :  XMLFile
    {
        public static int NEWER_DUNGEON = 1000;
        public int id;
        public List<GeneralPos> generalList;
        public List<GeneralTalk> preTalks;          ///进入副本前的对话
        public List<GeneralTalk> sceneTalks;        ///开始战斗的对话
        public List<GeneralTalk> endTalks;          ///结束战斗的对话
        public int chapter;
        public int x;
        public int y;
        public int energy;    //体力消耗
        public List<Data.ItemCount> drops;
        public bool elite
        {
            get
            {
                return DungeonData.Get(id).define == DugenonDefine.Elite;
            }
        }

        private static Dictionary<int, DungeonWar> m_dataMap;

        public static Dictionary<int, DungeonWar> dataMap
        {
            get
            {
                if (m_dataMap == null)
                    m_dataMap = new Dictionary<int, DungeonWar>();
                return m_dataMap;
            }
        }
        public static DungeonWar Get(int id)
        {
            DungeonWar war = null;
            if (!dataMap.TryGetValue(id, out war))
            {
                string filepath ="data/xml/dugeonWar/section_" + id.ToString();
                war = AResource.LoadXML<DungeonWar>(filepath);
                if (war != null)
                {
                    dataMap.Add(id, war);
                }
                else
                {
                    ALog.logError(filepath + " doesnot exist!");
                }
            }

            return war;
        }
        public GeneralData boss
        {
            get
            {
                foreach (var gen in generalList)
                {
                    if (gen.x == FormationPos.Centre && gen.y == FormationType.Middle)
                        return GeneralData.Get(gen.generalID);
                }
                return GeneralData.Get(generalList[0].generalID);
            }
        }

        public DungeonData baseInfo
        {
            get
            {
                return DungeonData.Get(id);
            }
        }

        public DungeonChapterData chapterData
        {
            get
            {
                return DungeonChapterData.Get(chapter);
            }
        }


    }
}
