#include <iostream>
#include <thread>			//Needed for std::thread
#include <cstring>			//Needed for memset and string functions
#include <queue>			//Needed for std::queue
#include <unistd.h>			//Needed for sleep
#include "TCPServerBase.h"
#include "SocketHub.h"

#define BACKLOG 5			//Maximum number of connection waiting to be accepted
#define TIMEOUT_SEC 3		//Timeout parameter for select() - in seconds
#define TIMEOUT_USEC 0		//Timeout parameter for select() - in micro seconds

namespace Servers {
    ServerParam::ServerParam()
        : port(0)
        , handler(nullptr) {
    }

    TCPServerBase::TCPServerBase(const TCPServerBase &other)
        : param_(other.getParams())
        , socket_(nullptr)
        , maxFD_(0)
        , running_(true) {
    }

    TCPServerBase::TCPServerBase(const ServerParam& param)
        :param_(param)
        , running_(true) {
    }


    const ServerParam& TCPServerBase::getParams() const {
        return this->param_;
    }

    TCPServerBase& TCPServerBase::operator=(const TCPServerBase &other) {
        if (&other == this)
            return *this;
        else {
            this->param_ = other.getParams();
            this->running_ = true;
            return *this;
        }
    }

    TCPServerBase::~TCPServerBase() {
        this->stop();
    }

    void TCPServerBase::start() {
        running_ = true;
        thread_ = std::thread(&TCPServerBase::run, this);
    }

    void TCPServerBase::stop() {
        if (socket_) {
            socket_->closeAll(maxFD_);
            delete socket_;
        }
        running_ = false;
        if (thread_.joinable())
            thread_.join();
    }

    void TCPServerBase::send(int clientFD, char* buffer, size_t length) {
        if (socket_)
            socket_->sendMessage(clientFD, buffer, length);
    }

    /**
     * This method is the servers main routine.
     * 		1. Creates a listener socket and bind it to the given port
     * 		2. Start listening on the given port.
     * 		3. Sets all sockets to be non-blocking.
     * 		4. Creates a set to hold all active sockets (connection)
     * 		5. While running flag is true:
     * 			5.1 Check for changes in active sockets.
     * 			5.2 If listener socket has new connection - Accept it and add to set.
     * 			5.3 If some client socket received data (bytes > 0) - Handle it.
     * 		6. Close all sockets - terminate server.
     */
    void TCPServerBase::run() {

        int listenerFD = 0;		//Listener socket
        socket_ = new SocketHub();
        //Wraps the sockets detailed implementation. See SocketWrapper for details.
        socket_->setServerHandler(param_.handler);
        // 1.
        if (!socket_->bindOnPort(param_.port, listenerFD))
            return;
        // 2.
        socket_->listenSocket(listenerFD, BACKLOG);
        cout << "Listening on port " << param_.port << "..." << endl;

        // 3.
        socket_->setNonBlock(listenerFD);

        // 4.
        socket_->createSets(listenerFD);
        maxFD_ = listenerFD;

        // 5.
        while (running_) {
            //5.1
            socket_->selectSockets(maxFD_, TIMEOUT_SEC, TIMEOUT_USEC);
            int newClientFD = 0;
            if (socket_->checkNewConnection(listenerFD, newClientFD, clientHost_)) {
                if (newClientFD > maxFD_)
                    maxFD_ = newClientFD;
                onConnect(newClientFD, clientHost_);
            }
            for (int i = 0; i < maxFD_ + 1; i++) {
                if (i == listenerFD)
                    continue;
                if (socket_->canRead(i)) {
                    int bytes = socket_->receiveMessage(i);
                    if (bytes > 0) {
                        onRecive(i, socket_->getBuffer(), bytes);
                    } else if (bytes < 0) {
                        socket_->removeClient(i, SocketCloseReason::ReceiveException);
                    } else if (bytes == 0) {
                        socket_->removeClient(i, SocketCloseReason::Client);
                    }
                } else {
                    //::sleep(5);
                }
            }
        }
        // 6.
        socket_->closeAll(maxFD_);
    }
    void TCPServerBase::onDisconnect(int clientFD, SocketCloseReason reason) {
        std::cout << "onDisconnect socket" << clientFD << " reason:" << reason << std::endl;
    }

    void TCPServerBase::onConnect(int clientFD, const std::string clientHost_) {
        std::cout << "onConnect " << clientHost_ << " socket " << clientFD << std::endl;
        if (param_.handler != nullptr)
            param_.handler->onConnect(clientFD, clientHost_);
    }

    void TCPServerBase::onRecive(int clientFD, const char* buffer, int length) {
        if (param_.handler != nullptr)
            param_.handler->onRecive(clientFD, buffer, length);
    }
}
