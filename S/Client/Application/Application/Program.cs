using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Application
{
    class Program
    {
        static void Main(string[] args)
        {
            Net net = new Net();
            LoginParam param = new LoginParam();
            param.user = "160";
            param.psw = "1111111";
            param.host = "127.0.0.1";
            param.port = 15299;
            net.ConnectLoginServer(param);
            while (true)
            {
                net.Update();
                System.Threading.Thread.Sleep(10);
            }
        }
    }
}
