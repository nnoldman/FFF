#include <cstdio>
#include <iostream>
#include "Test_Env.h"
//#include "TcpServer.h"
#include "Environment.h"
#include "ServerExecuter.h"

int main() {
    Test_Env env;
    //GameFrame::TcpServer server;
    //Servers::ServerParam params;
    //params.port = 7800;
    //params.handler = &server;
    //server.start(params);
    Frame::ServerExecuter server;
    server.start(7800);
    Environment::sleep(500000000);
    return 0;
}
