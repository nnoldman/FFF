using Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class SignData : GameData<SignData>
    {
        static public readonly string fileName = "xml/Sign";

        public Data.ItemCount itemCount;
        public int minvip;
        public string texture
        {
            get
            {
                ObjectBase def = ObjectBase.Get(itemCount.id);
                if(def!=null)
                    return def.texture;
                return null;
            }
        }
    }
}
