#ifndef HServer_h__
#define HServer_h__

#include "Poco/Net/HTTPServer.h"
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

#endif // HServer_h__
