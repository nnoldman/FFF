#ifndef IServerHandler_h__
#define IServerHandler_h__
#include <string>
namespace Servers {
    enum SocketCloseReason {
        ReceiveException,
        Client,
        SendException,
        Server,
    };
    class IServerHandler {
      public:
        virtual void onDisconnect(int clientFD, SocketCloseReason reason) = 0;
        virtual void onConnect(int clientFD, const std::string host) = 0;
        virtual void onRecive(int clientFD, const char* buffer, size_t length) = 0;
        virtual void send(int clientFD, char* buffer, size_t length) = 0;
    };
}

#endif // IServerHandler_h__
