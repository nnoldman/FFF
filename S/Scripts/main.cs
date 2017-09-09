using ProtoBuf.Meta;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace DataBase
{
    public class main
    {
        public static int Main()
        {
            test_deserialize_from_sql_record();

            test_attribute();

            test_pkg_serialize();

            test_call_remote();

            test_create_and_insertto_db();

            //List<string> arr = DBSerializer.getDBValues(account);
            //string tabname = account.tableName;
            //object obj = account.fetchByField("user");

            //DataInitializer dier = new DataInitializer();
            //dier.Init();

            return 0;
        }
        public static void test_deserialize_from_sql_record()
        {
            string[] arr = new string[] { "123","111111","","5","","JKKKKKKKKKKKKJKLLJLK" };
            Account acc = new Account();
            DBSerializer.deserializePKGFromSQL(arr, acc);
        }
        public static void test_create_and_insertto_db()
        {
            DataBase.Account account = new Account();
            account.createAndInsertToDB();
        }
        public static void test_attribute()
        {
            Type type = typeof(DataBase.Account);
            object[] attrs= type.GetCustomAttributes(true);
            foreach(var att in attrs)
            {
                if(att.GetType()==typeof(DB))
                {
                    DB db = (DB)att;
                    Debug.Assert(db.dbtype == DBType.Defalut || db.dbtype == DBType.Table);
                }
            }
            //IList<CustomAttributeData> custom_attributes= type.GetCustomAttributes(true);
            //Debug.Assert(DataBase.DBSerializer.getDBType())
        }
        public static void test_call_remote()
        {
            S_Account sp = new S_Account();
            string sm = sp.callClient("onEnterWorld", 15, "ShanHaiGuan");
            Console.WriteLine(sm);
        }
        public static void test_pkg_serialize()
        {
            DataBase.Account account = new Account();
            account.guid = "guillllll";
            account.user = "90432";
            account.psw = "fjsadlkf";
            account.roles = new List<int>();
            for (int i=0;i<4;++i)
            {
                account.roles.Add(i);
            }
            account.test = 45;
            account.active_role = account.roles[0];

            string conent = DBSerializer.serializePKG(account);
            DataBase.Account res = (DataBase.Account)DBSerializer.deserializePKG(conent);
            System.Diagnostics.Debug.Assert(res.test == 45);
            System.Diagnostics.Debug.Assert(res.psw == "fjsadlkf");
        }
    }
}
