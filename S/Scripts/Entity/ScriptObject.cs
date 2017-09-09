using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Xml;

namespace DataBase
{
    public class ScriptObject
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void DB_SyncClient(string account_guid, string data);

        protected DataBase.DBPkg mDBInterface;
        public string guid()
        {
            return "xfjcdej";
        }
        public virtual void onSync()
        {
        }

        public virtual void SyncClient(DBPkg pkg)
        {
            Console.WriteLine("sync: " + pkg.GetType().Name);
            string data = DBSerializer.serializePKG(pkg);
            Console.WriteLine("SyncClient: " + data);
            DB_SyncClient(mDBInterface.guid, data);
        }
        public string callClient(string method, params object[] args)
        {
            return string.Empty;
            //RemoteFunction remotefun = new RemoteFunction();
            //remotefun.method = method;
            //remotefun.args = args;
            //remotefun.guid = guid();
            //remotefun.type = GetType().Name;
            //return remotefun.serialize();
        }
        public void sendCmd(ICommand cmd)
        {

        }
    }
}
