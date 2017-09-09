using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum GameUI
{
    WarMap,
    WarMapChapter,
    General,
    Barrack,
    GeneralSkill,
}

namespace GameData
{
    public class PostLoadingData : GameData<PostLoadingData>
    {
        static public readonly string fileName = "xml/PostLoadingData";
        public GameUI type;
        public int icon;
        public int name;
        public string texture
        {
            get
            {
                try
                {
                    return IconData.Get(icon).texture;
                }
                catch
                {
                    return null;
                }
            }
        }
        public string nameString
        {
            get
            {
                return Localization.Get(name);
            }
        }
    }
}