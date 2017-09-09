using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace GameData
{
    public enum SourceType
    {
        Dungeon,        //副本
        Count,
    }
    public class Source : GameData<Source>
    {
        static public readonly string fileName = "xml/Source";
        public SourceType sourceType;
        public int sourceID;
    }
}