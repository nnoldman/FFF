#ifndef HttpService_h__
#define HttpService_h__


#include "Poco/Net/HTTPServer.h"
class HttpService:public IService<HttpService> {
  public:
    HttpService();
    ~HttpService();
    virtual bool start() override;
    virtual const char* name() override;
  private:
    Poco::Net::HTTPServer*    server_;
    u16 port_;
};

#endif // HttpService_h__
