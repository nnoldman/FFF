#ifndef TCPServerBase_h__
#define TCPServerBase_h__
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include "SocketHub.h"
#include "IServerHandler.h"
using namespace std;
namespace Servers {
    struct ServerParam {
        unsigned short port;
        IServerHandler* handler;
        ServerParam();
        ServerParam(const ServerParam& other) = default;
    };
    class TCPServerBase {
      public:
        TCPServerBase(const ServerParam& param);
        TCPServerBase(const TCPServerBase &other);
        TCPServerBase& operator=(const TCPServerBase &other);
        const ServerParam& getParams() const;
        virtual ~TCPServerBase();
        void start();
        void stop();
        void send(int clientFD, char* buffer, size_t length);
      private:
        void run();
        void onDisconnect(int clientFD, SocketCloseReason reason);
        void onConnect(int clientFD, const std::string host);
        void onRecive(int clientFD, const char* buffer, int length);
      private:
        ServerParam param_;
        std::thread thread_;
        SocketHub* socket_;
        string clientHost_;
        int maxFD_;				//Hold the maximum file descriptor number from the active sockets
        bool running_;
    };
}
#endif // TCPServerBase_h__
