using System;
using System.Collections.Generic;
using System.Text;
/// <summary>
/// 材料合成
/// </summary>
namespace GameData
{
    public class MaterialData : GameData<MaterialData>
    {
        static public readonly string fileName = "xml/MaterialData";

        public int cost;
        public Data.ItemCount needMetrials;
        public List<int> source;
        public string texture
        {
            get
            {
                var def = ObjectBase.Get(id);
                if (def!=null)
                {
                    return def.texture;
                }
                return null;
            }
        }
        public ObjectBase define
        {
            get
            {
                return ObjectBase.Get(id);
            }
        }
    }
}

