using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataBase
{
    public enum DBType
    {
        Defalut,
        Table,
        IntArray,   //bulk
    }
    public class DB:Attribute
    {
        public bool Key = false;
        public DB(DBType type = DBType.Defalut, string def = null)
        {
            mDefine = def;
            mType = type;
        }
        public DBType dbtype
        {
            get{
                return mType;
            }
        }
        protected string mDefine;
        protected DBType mType = DBType.Defalut;
    }
}
