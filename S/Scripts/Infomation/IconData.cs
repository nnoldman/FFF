/*----------------------------------------------------------------
// 模块名：IconData
// 模块描述：
//----------------------------------------------------------------*/
using System.Collections;
using System.Collections.Generic;
using System;

namespace GameData
{
    public class IconData : GameData<IconData>
    {
        private const int PORTRAIT = 309;
        public string path;
        public int color;
        static public readonly string fileName = "xml/Icon";

        static public string none { get { return "emptyItem"; } }

        public string texture
        {
            get
            {
                return path;
            }
        }
        public IconData()
        {
            path = string.Empty;
        }

        static public string GetIconPath(int id)
        {
            if (dataMap.ContainsKey(id))
                return dataMap[id].path;
            return null;
        }
    }
}
