#ifndef TcpServer_h__
#define TcpServer_h__
#include "IServerHandler.h"
#include <mutex>
#include <vector>
#include "TCPServerBase.h"
namespace GameFrame {
    class Message {
      public:
        ~Message();
        int clientFD;
        size_t count;
        char data[0];
        static Message* create(int clientFD, const char* data, size_t count);
      private:
        Message();
    };
    class TcpServer :public Servers::IServerHandler {
      public:
        TcpServer();
        ~TcpServer();
        const std::vector<Message*>& getReceiveMessages() const;
        void lockReceiveMessages();
        void unlockReceiveMessages();
        void clearReceiveMessages();
        bool start(const Servers::ServerParam& params);
        virtual void send(int clientFD, char* buffer, size_t length) override;
      protected:
        virtual void onDisconnect(int clientFD, Servers::SocketCloseReason reason) override;
        virtual void onConnect(int clientFD, const std::string host) override;
        virtual void onRecive(int clientFD, const char* buffer, size_t length) override;
      private:
        Servers::TCPServerBase* serverBase_;
        std::vector<Message*> receiveMessages_;
        std::mutex receiveLocker_;
    };
}


#endif // TcpServer_h__
