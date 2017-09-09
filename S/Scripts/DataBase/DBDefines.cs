using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataBase
{
    public enum CommonState
    {
        None,
        CanFetch,
        Fetched,
    }

    [DB(DBType.Table)]
    public class Account : DBPkg
    {
        [DB(Key = true)]
        public int id = 0;

        [DB(Key = true)]
        public string user = "123";

        [DB]
        public string psw;

        [DB]
        public List<int> roles;

        [DB]
        public int test = 5;

        [DB]
        public int active_role;
    }
    [DB(DBType.Table)]
    public class Role : DBPkg
    {
        [DB(Key = true)]
        public int index;

        [DB]
        public string name;

        [DB]
        public bool sex;

        [DB]
        public uint lastLoginTime;

        [DB]
        public uint sceneid;

        [DB]
        public Sign sign;
    }
    public class Sign
    {
        [DB]
        public int count;

        [DB]
        public List<CommonState> states;
    }

    [DB(DBType.Table)]
    public class Soldier : DBPkg
    {
        [DB]
        public int type = 0;

        [DB]
        public byte star = 1;

        [DB]
        public string name;

        [DB]
        public uint exp = 0;

        [DB]
        public uint general = 0;
    }
}
