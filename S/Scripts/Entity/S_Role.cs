using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
namespace DataBase
{
    public class S_Role : ScriptObject
    {
        public S_Role()
        {
            Console.WriteLine("S_Role ctor ...");
        }

        public void enterScene()
        {
            mDBInterface.sync();
        }
    }
}
