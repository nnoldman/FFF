using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;

namespace DataBase
{
    public enum DBOperation
    {
        Refresh,
        Delete,
    }
    public class DBPkg
    {

        [DB]
        public string guid;

        protected List<DBPkg> mDBList;

        public DBPkg()
        {
            Console.WriteLine("DBPKG ..."+GetType().Name);

        }

        protected void addChild<T>(string guid) where T : DBPkg
        {
            Debug.Assert(!string.IsNullOrEmpty(guid));

            Type tp = typeof(T);
            DBPkg db = (DBPkg)tp.GetConstructor(Type.EmptyTypes).Invoke(null);
            Debug.Assert(db);
            FieldInfo info = tp.GetField("guid");
            Debug.Assert(info != null);
            info.SetValue(db, guid);
            db.fetch();
            mDBList.Add(db);
        }

        public static implicit operator bool (DBPkg db)
        {
            return db != null;
        }

        public string tableName
        {
            get
            {
                return DBSerializer.isTable(GetType()) ? ("yw_" + GetType().Name).ToLower() : string.Empty;
            }
        }
        public bool fetchByField(string field)
        {
            Console.WriteLine("fetchByField1:" + field);
            FieldInfo fi = GetType().GetField(field);

            object ofield = null;
            if (fi != null)
                ofield = fi.GetValue(this);

            if (ofield != null)
            {
                string cmd = string.Format("SELECT * FROM {0} WHERE {1}='{2}';", tableName, field, ofield.ToString());
                return DataInitializer.DB_queryToScriptObject(cmd, this);
            }
            Console.WriteLine("fetchByField2:"+field);
            return false;
        }
        public void fetch()
        {
            fetchByField("guid");
            this.onFetch();
        }
        public void onCreate()
        {

        }
        public virtual void onFetch()
        {
        }
        public void save()
        {

        }
        public void remove()
        {

        }
        public virtual void sync()
        {
        }
        public void syncDB()
        {
        }

        public void fill(byte[] buffer)
        {

        }
        public bool saveToDB()
        {
            return true;
        }

        public bool createAndInsertToDB()
        {
            Console.WriteLine("createAndInsertToDB");
            //insert into yw_account(guid) values('8902');
            string cmdstring = "insert into " + tableName + " (";
            string values = "values(";

            Type tp = GetType();

            List<string> columns = DBSerializer.getDBColoumns(tp);
            List<string> defines = DBSerializer.getDBDefines(tp);

            for (int i = 0; i < columns.Count; ++i)
            {
                cmdstring += columns[i] + ",";
                FieldInfo field = tp.GetField(columns[i]);
                values += "'" + DBSerializer.serializeField(field.FieldType, field.GetValue(this)) + "',";
            }

            cmdstring = cmdstring.Remove(cmdstring.Length - 1);
            values = values.Remove(values.Length - 1);
            cmdstring = cmdstring + ") " + values + ");";
            Console.WriteLine("createAndInsertToDB:" + cmdstring);
            return DataInitializer.DB_insert(tableName, cmdstring); ;
        }
    }
}