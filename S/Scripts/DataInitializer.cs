using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
using System.Reflection;
using System.IO;
using System.Xml;

namespace DataBase
{
    public class DataInitializer
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static bool DB_hasTable(string name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        //[DllImport("..\\Debug\\Core.dll")]
        extern static bool DB_createEmptyTable(string name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static bool DB_createTable(string name, string cmd);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static bool DB_alterTableColumnAttribute(string name, string cmd);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static bool DB_queryToScriptObject(string cmd, object obj);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static bool DB_insert(string cmd, object obj);

        public DataInitializer()
        {
            //Console.WriteLine(Environment.StackTrace);
            //Console.WriteLine(Mono.CSharp.Evaluator.GetVars());
            //Mono.CSharp.Evaluator.Interrupt();
            //XmlDocument doc = new XmlDocument();
            //doc.CreateElement("root");
            //doc.Save("1234.xml");
            //Console.WriteLine("DataInitializer ...");
        }
        public int count = 6;
        public bool Init()
        {
            Console.WriteLine("DataInitializer ... Init");
            Console.Write("===>" + GetType().Name + " Init ");

            Assembly ass = typeof(DataInitializer).Assembly;

            var types = ass.GetTypes();

            foreach (var item in types)
            {
                if (item.Namespace == "DataBase")
                {
                    if (DBSerializer.isTable(item))
                    {
                        recreateDB(item);
                    }
                }
            }

            Console.Write("===>" + GetType().Name + " Init End ");

            return true;
        }

        private bool recreateDB(Type tp)
        {
            string tableName = "yw_" + tp.Name;
            tableName = tableName.ToLower();

            if (!DB_hasTable(tableName))
            {
                string cmd = getCreateString(tp);
                return DB_createTable(tableName, cmd);
            }
            return true;
        }



        private bool isType(object mem, Type tp)
        {
            return 0 == string.Compare(mem.ToString(), tp.Name);
        }
        private string getCreateString(Type tp)
        {
            string cmdString = "(";

            List<string> columns = DBSerializer.getDBColoumns(tp);
            List<string> defines = DBSerializer.getDBDefines(tp);

            for (int i = 0; i < columns.Count; ++i)
            {
                cmdString += columns[i];
                cmdString += " " + defines[i] + ",";
            }

            cmdString = cmdString.Remove(cmdString.Length - 1, 1);
            cmdString += ");";
            Console.WriteLine("CmdString: " + cmdString);
            return cmdString;
        }

        public static bool deseriallize(string[] stringarray, object obj)
        {
            Console.WriteLine("deseriallize:");
            obj = DBSerializer.deserializePKGFromSQL(stringarray, obj);
            return true;
        }
        public static string[] serialize(object obj)
        {
            return null;
        }
    }
}
