#ifndef NetService_h__
#define NetService_h__


#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Mutex.h"
#include "IService.h"
#include "../net/ProtocoBuffer.h"
#include "../net/Connection.h"
#include "../net/NetOption.h"

class COREAPI NetService :public IService<NetService> {
  public:
    Basic::Delegate2<void, ProtocoBuffer*, Connection*> onMessage;
    Basic::Delegate1<void, Connection*> onDisconnect;
    Basic::Delegate1<void, Connection*> onConnect;
  public:
    struct Packet {
        u32 len;
        char* data;
        Connection* con;
        Packet() : len(0), data(nullptr), con(nullptr) {
        };
        ~Packet() {
            delete[] data;
        }
    };
  public:
    NetService();
    ~NetService();
    virtual bool start() override;
    virtual const char * name() override;
    void tick();
    void addMessage(void* data, u32 len, Connection* con);
  private:
    bool initialize(const NetOption& config);
  private:
    Poco::Mutex mLock;
    std::vector<Packet*> mDataArray;
    Poco::Net::TCPServer* mServer;
    NetOption option_;
};

#endif // NetService_h__
