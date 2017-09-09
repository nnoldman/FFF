using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Xml;

namespace DataBase
{
    public class ReturnValue
    {
        public List<string> coloumns;
        public List<string> values;
    }
    public class DBSerializer
    {
        public static char ListSeparation = ';';
        public static DBType getDBType(Type type)
        {
            object[] attrs = type.GetCustomAttributes(true);
            foreach (var att in attrs)
            {
                if (att.GetType() == typeof(DB))
                {
                    DB db = (DB)att;
                    return db.dbtype;
                }
            }
            return DBType.Defalut;
        }
        public static DBType getDBType(FieldInfo field)
        {
            object[] attrs = field.GetCustomAttributes(true);
            foreach (var att in attrs)
            {
                if (att.GetType() == typeof(DB))
                {
                    DB db = (DB)att;
                    return db.dbtype;
                }
            }
            return DBType.Defalut;
        }
        public static bool isTable(Type type)
        {
            return DBType.Table == getDBType(type);
        }
        public static List<string> getDBColoumns(Type type)
        {
            if (!isTable(type))
                return null;
            List<string> strarray = new List<string>();

            FieldInfo[] fields = type.GetFields();
            foreach (FieldInfo field in fields)
            {
                if (getDBType(field) == DBType.Defalut && !IsSqlKeyWord(field.Name))
                    strarray.Add(field.Name);
            }
            return strarray;
        }
        public static DBPkg deserializePKGFromSQL(string[] content, object pkg)
        {
            FieldInfo[] fields = pkg.GetType().GetFields();
            int i = 0;
            foreach (FieldInfo field in fields)
            {
                if (getDBType(field) == DBType.Defalut)
                {
                    object of= deserializedField(field, content[i]);
                    field.SetValue(pkg, of);
                    ++i;
                }
            }
            foreach (FieldInfo field in fields)
            {
                if (getDBType(field) == DBType.Defalut)
                {
                    object of = field.GetValue(pkg);
                    if(of!=null)
                        Console.WriteLine("FV:" + field.Name + of.ToString());
                }
            }
            return (DBPkg)pkg;
        }
        public static DBPkg deserializePKG(string content)
        {

            MemoryStream ms = new MemoryStream(Encoding.UTF8.GetBytes(content));
            XmlDocument doc = new XmlDocument();
            doc.Load(ms);

            XmlNode root = doc.FirstChild;

            string stype = root.Attributes["type"].Value;
            object dbpkg = typeof(DBSerializer).Assembly.CreateInstance(stype);
            if (dbpkg != null)
            {
                DBPkg pkg = (DBPkg)dbpkg;
                pkg.guid = root.Attributes["guid"].Value;

                if (root.ChildNodes != null)
                {
                    foreach (XmlNode child in root.ChildNodes)
                    {
                        string fieldname = child.Attributes["name"].Value;
                        string filedcontent = child.Attributes["value"].Value;
                        FieldInfo field = pkg.GetType().GetField(fieldname);
                        object objfield = DBSerializer.deserializedField(field, filedcontent);
                        field.SetValue(dbpkg, objfield);
                    }
                }
            }
            return (DBPkg)dbpkg;
        }
        public static string serializePKG(DBPkg pkg)
        {
            Console.WriteLine("serializePKG");
            Type tp = pkg.GetType();
            List<string> columns = DBSerializer.getDBColoumns(tp);
            Console.WriteLine("serializePKG" + columns.Count.ToString());

            XmlDocument doc = new XmlDocument();
            XmlElement root = doc.CreateElement("db_data");
            doc.AppendChild(root);

            root.SetAttribute("type", tp.FullName);
            root.SetAttribute("guid", pkg.guid);

            for (int i = 0; i < columns.Count; ++i)
            {
                XmlElement argnode = doc.CreateElement("field");
                root.AppendChild(argnode);
                FieldInfo field = tp.GetField(columns[i]);
                argnode.SetAttribute("type", field.FieldType.Name);
                argnode.SetAttribute("name", columns[i]);
                argnode.SetAttribute("value", DBSerializer.serializeField(field.FieldType, field.GetValue(pkg)));
            }

            System.IO.MemoryStream ms = new System.IO.MemoryStream(1024);
            doc.Save(ms);
            return Encoding.UTF8.GetString(ms.ToArray());
        }
        public object deserialize(string data)
        {
            return null;
        }
        public static string serializeField(Type tp, object fieldobj)
        {
            if (fieldobj == null)
                return string.Empty;

            Type proptype = tp;

            if (proptype.IsGenericType && proptype.GetGenericTypeDefinition() == typeof(List<>))
            {
                Type listParamType = proptype.GetGenericArguments()[0];
                if (fieldobj == null)
                    return string.Empty;

                int cnt = (int)proptype.GetProperty("Count").GetValue(fieldobj, null);

                StringBuilder sb = new StringBuilder();

                for (int i = 0; i < cnt; ++i)
                {
                    object[] args = new object[1];
                    args[0] = i;

                    PropertyInfo propinfo = proptype.GetProperty("Item");

                    object item = propinfo.GetValue(fieldobj, args);
                    string itemstr = Data.Converter.GetString(item.GetType(), item);
                    if (itemstr.Length > 0)
                    {
                        sb.Append(itemstr);
                        sb.Append(ListSeparation);
                    }
                }
                return sb.ToString();
            }
            else
            {
                return Data.Converter.GetString(proptype, fieldobj);
            }
        }
        public static object deserializedField(FieldInfo prop, string value)
        {
            if (string.IsNullOrEmpty(value))
                return null;

            Type proptype = prop.FieldType;


            if (proptype.IsGenericType && proptype.GetGenericTypeDefinition() == typeof(List<>))
            {
                object objfield = proptype.GetConstructor(Type.EmptyTypes).Invoke(null);
                Type listParamType = proptype.GetGenericArguments()[0];

                String[] arrays = value.Split(ListSeparation);

                for (int i = 0; i < arrays.Length; ++i)
                {
                    object arr_element = Data.Converter.GetValue(listParamType, arrays[i]);
                    proptype.GetMethod("Add").Invoke(objfield, new object[] { arr_element });
                }
                return objfield;
            }
            else
            {
                return Data.Converter.GetValue(proptype, value);
            }
        }
        public static string serializeField(FieldInfo prop, object obj)
        {
            object childValue = prop.GetValue(obj);
            return serializeField(prop.FieldType, childValue);
        }
        public static List<string> getDBValues(object obj)
        {
            Type type = obj.GetType();
            if (!isTable(type))
                return null;
            List<string> strarray = getDBColoumns(type);
            List<string> valueArray = new List<string>();

            foreach (string fieldname in strarray)
            {
                FieldInfo field = type.GetField(fieldname);
                if (field != null)
                    valueArray.Add(serializeField(field, obj));
            }

            return valueArray;
        }
        public static List<string> getDBDefines(Type type)
        {
            List<string> strarray = getDBColoumns(type);
            List<string> valueArray = new List<string>();

            foreach (string fieldname in strarray)
            {
                FieldInfo field = type.GetField(fieldname);
                if (field != null)
                    valueArray.Add(DBDefiner.Instance.GetCmd(field));
            }
            return valueArray;
        }
        static bool IsSqlKeyWord(string filed)
        {
            foreach (var k in SQL_KEY_WORDS)
            {
                if (k == filed)
                {
                    Console.WriteLine("IsSqlKeyWord True : " + k);
                    return true;
                }
            }
            return false;
        }
        static string[] SQL_KEY_WORDS = new string[] 
        {
            "index",
        };

    }
}
