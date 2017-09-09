using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
namespace DataBase
{
    public struct Element
    {
        public Type type;
        public string cmd;
        public Element(Type t, string c)
        {
            type = t;
            cmd = c;
        }
    }
    public class DBDefiner
    {
        public static DBDefiner Instance
        {
            get
            {
                if (mInstance == null)
                    mInstance = new DBDefiner();
                return mInstance;
            }
        }

        static DBDefiner mInstance;

        Element[] mElements;

        DBDefiner()
        {
            mElements = new Element[]{

                        new Element( typeof(System.String),"TEXT" ),
                        new Element( typeof(string),"TEXT" ),

                        new Element( typeof(byte),"TINYINT" ),
                        new Element( typeof(bool),"TINYINT" ),
                        new Element( typeof(Boolean),"TINYINT" ),

                        new Element( typeof(short),"SMALLINT" ),
                        new Element( typeof(ushort),"SMALLINT" ),
                        new Element( typeof(UInt16),"SMALLINT" ),

                        new Element( typeof(int),"INT" ),
                        new Element( typeof(uint),"INT" ),
                        new Element( typeof(UInt32),"INT" ),

                        new Element( typeof(UInt64),"BIGINT" ),

                        new Element( typeof(float),"FLOAT" ),
                        new Element( typeof(double),"DOUBLE" ),
                        new Element( typeof(List<>),"BLOB" ),

                    };
        }
        public string GetCmd(FieldInfo obj)
        {
            foreach (var e in mElements)
            {
                if (obj.FieldType.IsGenericType)
                {
                    if (obj.FieldType.GetGenericTypeDefinition() == e.type)
                    {
                        return e.cmd;
                    }
                }
                else if (obj.FieldType.Name == e.type.Name)
                {
                    return e.cmd;
                }
            }
            return "BLOB";
        }
    }
}
