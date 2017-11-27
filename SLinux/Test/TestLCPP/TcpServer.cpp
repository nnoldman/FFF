#include "TcpServer.h"
#include "TCPServerBase.h"
#include <string>
#include <iostream>
#include <memory>
#include<string.h>
namespace GameFrame {
    Message::~Message() {
        delete[] (char*)this;
    }
    Message::Message()
        :clientFD(0)
        , count(0) {
    }


    Message* Message::create(int clientFD, const  char* data, size_t count) {
        if (count > 0) {
            void* address = new char[sizeof(Message) + count];
            Message* msg = ::new (address) Message;
            msg->clientFD = clientFD;
            msg->count = count;
            memcpy(msg->data, data, count);
            return msg;
        }
        return nullptr;
    }

    TcpServer::TcpServer()
        :serverBase_(nullptr) {
    }

    TcpServer::~TcpServer() {
        if (serverBase_)
            serverBase_->stop();
    }

    void TcpServer::onDisconnect(int clientFD, Servers::SocketCloseReason reason) {
    }

    void TcpServer::onConnect(int clientFD, const std::string host) {
    }

    void TcpServer::onRecive(int clientFD, const char* buffer, size_t length) {
        auto* msg = Message::create(clientFD, buffer, length);
        this->receiveLocker_.lock();
        this->receiveMessages_.push_back(msg);
        this->receiveLocker_.unlock();
    }

    void TcpServer::send(int clientFD, char* buffer, size_t length) {
        this->serverBase_->send(clientFD,buffer,length);
    }

    void TcpServer::clearReceiveMessages() {
        for (auto it : this->receiveMessages_)
            delete it;
        this->receiveMessages_.clear();
    }

    bool TcpServer::start(const Servers::ServerParam& param) {
        serverBase_ = new Servers::TCPServerBase(param);
        serverBase_->start();
        return true;
    }

    const std::vector<Message*>& TcpServer::getReceiveMessages() const {
        return this->receiveMessages_;
    }

    void TcpServer::lockReceiveMessages() {
        this->receiveLocker_.lock();
    }

    void TcpServer::unlockReceiveMessages() {
        this->receiveLocker_.unlock();
    }
}

