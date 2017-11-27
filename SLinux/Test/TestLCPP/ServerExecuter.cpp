#include "ServerExecuter.h"
#include <iostream>
#include <functional>
namespace Frame {
    ServerExecuter::ServerExecuter()
        : eventHandler_(nullptr)
        , running_(true) {
    }

    ServerExecuter::~ServerExecuter() {
        this->close();
    }

    void ServerExecuter::start(unsigned short port) {
        eventHandler_ = new handy::EventBase();
        handy::Signal::signal(SIGINT, std::bind(&ServerExecuter::close,this));
        server_ = handy::HSHA::startServer(eventHandler_, "", port, 4);
        exitif(server_ == NULL, "start tcp server failed");
        server_->server_->onConnCreate(std::bind(&ServerExecuter::onConnect, this));
        server_->server_->onConnState(std::bind(&ServerExecuter::onStateChange, this, std::placeholders::_1));
        server_->server_->onConnRead(std::bind(&ServerExecuter::onReceive, this, std::placeholders::_1));
        worker_ = std::thread(&ServerExecuter::loop, this);
    }

    void ServerExecuter::onReceive(const handy::TcpConnPtr& connection) {
        std::cout << "onReceive:" << connection->str() << std::endl;
        if (connection->getChannel()->readEnabled()) {
            std::cout << "readEnabled size:" << connection->getInput().size() << std::endl;
            connection->getInput().clear();
        }
    }

    //std::string ServerExecuter::onMessage(const handy::TcpConnPtr& connection, const std::string& msg) {
    //    std::cout << "onMessage:" << msg << std::endl;
    //    return msg;
    //}

    void ServerExecuter::loop() {
        if(eventHandler_)
            eventHandler_->loop();
    }

    handy::TcpConnPtr ServerExecuter::onConnect() {
        handy::TcpConnPtr connection(new handy::TcpConn());
        //connection->onRead(std::bind(&ServerExecuter::onReceive, this, std::placeholders::_1));
        return connection;
    }

    void ServerExecuter::onStateChange(const handy::TcpConnPtr& connection) {
        auto state = connection->getState();
        switch (state) {
        default:
            break;
        case handy::TcpConn::Invalid:
            std::cout << "Invalid:" << connection->str() << std::endl;
            break;
        case handy::TcpConn::Handshaking:
            std::cout << "Handshaking:" << connection->str() << std::endl;
            break;
        case handy::TcpConn::Connected:
            std::cout << "Connected:" << connection->str() << std::endl;
            break;
        case handy::TcpConn::Closed:
            std::cout << "Closed:" << connection->str() << std::endl;
            break;
        case handy::TcpConn::Failed:
            std::cout << "Failed:" << connection->str() << std::endl;
            break;
        }
    }

    void ServerExecuter::close() {
        if (running_) {
            if (worker_.joinable())
                worker_.join();
            if (eventHandler_) {
                eventHandler_->exit();
                delete eventHandler_;
                eventHandler_ = nullptr;
            }
            running_ = false;
        }
    }
}
