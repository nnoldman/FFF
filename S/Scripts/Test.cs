using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Scripts
{
    public class Test
    {
        public void testVoid()
        {
            Console.WriteLine("\nTest::testVoid");
        }

        public void testParam(string strpara,int intpara)
        {
            Console.WriteLine("\nTest::testStringParam: " + strpara + intpara.ToString());
        }
    }
}
