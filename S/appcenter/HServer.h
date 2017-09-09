#pragma once
#include "..\include\Poco\Net\HTTPServer.h"
class HServer
{
public:
    HServer();
    ~HServer();

    void Start();
private:
    Poco::Net::HTTPServer*    server_;
    u16 port_;
};

