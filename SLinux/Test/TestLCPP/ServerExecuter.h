#ifndef ServerExecuter_h__
#define ServerExecuter_h__
#include "handy/handy.h"
#include <string>
#include <thread>
namespace Frame {
    class ServerExecuter {
      public:
        ServerExecuter();
        ~ServerExecuter();
        void start(unsigned short port);

        handy::TcpConnPtr onConnect();
        void onReceive(const handy::TcpConnPtr& connection);
        void onStateChange(const handy::TcpConnPtr& connection);
        void close();
      private:
        void loop();
      private:
        handy::EventBase* eventHandler_;
        handy::HSHAPtr server_;
        std::thread worker_;
        bool running_;
    };
}


#endif // ServerExecuter_h__
