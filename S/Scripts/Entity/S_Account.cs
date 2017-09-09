using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

//
namespace DataBase
{
    public class S_Account 
        : ScriptObject
    {
        public int test = 5;
        public S_Account()
        {
            Console.WriteLine("S_Account:"+ GetType().Name);
            FieldInfo[] fis = this.GetType().GetFields();

            foreach (var fi in fis)
            {
                Console.WriteLine("DBPKG:" + fi.FieldType.Name);
                object of = fi.GetValue(this);
                if (of != null)
                    Console.WriteLine("DBPKGValue:" + of.ToString());
            }
        }
        public void onInitEnd()
        {
            Console.WriteLine("onInitEnd: " + mDBInterface.GetType().Name);

        }
        public void enterWorld()
        {
            Console.WriteLine("enterWorld ctor ...");

            this.SyncClient(mDBInterface);
        }

        public void callClient(string method, string args)
        {

        }

    }
}
