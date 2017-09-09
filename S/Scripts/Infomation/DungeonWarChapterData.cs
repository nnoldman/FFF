using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class DungeonChapterData : GameData<DungeonChapterData>
    {
        static public readonly string fileName = "xml/DungeonChapterData";
        public string name;
        public int x;
        public int y;
        public List<int> dungeonsNormal = new List<int>();
        public List<int> dungeonsElite = new List<int>();
        public List<Data.ItemCount> starRewardNormal = new List<Data.ItemCount>();
        public List<Data.ItemCount> starRewardElite = new List<Data.ItemCount>();
        public bool elite = false;

        public List<int> GetDungeons(bool elite)
        {
            return elite ? dungeonsElite : dungeonsNormal;
        }
        public List<Data.ItemCount> GetStarReward(bool elite)
        {
            return elite ? starRewardElite : starRewardNormal;
        }
        public bool completed
        {
            get
            {
                foreach (var d in dungeonsNormal)
                {
                    StatDungeon dungeon = null;
                    if (Informations.Instance.dungeons.TryGetValue(id, out dungeon))
                    {
                        if (!dungeon.occupy)
                            return false;
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }
        }

        public string nameOfFull
        {
            get
            {
                string str = string.Format(Localization.Get(10600), LanguageData.GetChineseNum(id)) + " " + name;
                return str;
            }
        }
        public bool opened
        {
            get
            {
                if (dungeonsNormal.Count > 0)
                {
                    DungeonData gamedata = DungeonData.Get(dungeonsNormal[0]);
                    if (gamedata)
                        return gamedata.opened;
                }
                return false;
            }
        }

        public int MaintainStars(bool elite)
        {
                int myCount = 0;
                var duns = elite ? dungeonsElite : dungeonsNormal;
                foreach (var d in duns)
                {

                    StatDungeon dungeon = null;
                    if (Informations.Instance.dungeons.TryGetValue(id, out dungeon))
                    {
                        if(dungeon.occupy)
                            myCount += dungeon.star;
                    }
                }
                return myCount;
        }

        public DungeonChapterData pre
        {
            get
            {
                int nid = id - 1;
                return Get(nid);
            }
        }
        public DungeonChapterData next
        {
            get
            {
                int nid = id + 1;
                return Get(nid);
            }
        }

        public static DungeonChapterData GetChapter(int dungeonID,out bool elite)
        {
            elite = false;
            foreach (var chapter in dataMap)
            {
                if (chapter.Value.dungeonsNormal.IndexOf(dungeonID) != -1)
                {
                    elite = false;
                    return chapter.Value;
                }
                if (chapter.Value.dungeonsElite.IndexOf(dungeonID) != -1)
                {
                    elite = true;
                    return chapter.Value;
                }
            }
            return null;
        }
    }
}
