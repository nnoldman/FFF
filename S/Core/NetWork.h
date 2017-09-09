#pragma once

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/StreamSocket.h"
#include "ProtocoBuffer.h"
#include "Connection.h"
#include "ConfigInfo.h"
#include "Poco/Mutex.h"

class COREAPI NetWork {
  public:
    Delegate2<void, ProtocoBuffer*, Connection*> onMessage;
    Delegate1<void, Connection*> onDisconnect;
    Delegate1<void, Connection*> onConnect;
  public:
    struct Packet {
        u32 len;
        char* data;
        Connection* con;
        Packet() : data(nullptr), con(nullptr), len(0) {
        };
        ~Packet() {
            delete[] data;
        }
    };
  public:
    NetWork();
    ~NetWork();

    bool initialize(const NetConfig& config);

    void prosess();

    void addMessage(void* data, u32 len, Connection* con);

  private:

    Poco::Mutex mLock;

    Array<Packet*> mDataArray;

    Poco::Net::TCPServer* mServer;
};

