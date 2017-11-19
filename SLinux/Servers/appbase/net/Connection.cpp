#include "../appbase.h"
#include "Connection.h"
#include "Bundle.h"
#include "Poco/Net/NetException.h"
#include "../services/NetService.h"

const int kHeaderLength_ = 4;

void Connection::run() {
    Poco::Net::StreamSocket& ss = socket();
    try {
        buffer_.clear();
        while (!closed_) {
            if (ss.available() >= 0) {
                auto length = ss.receiveBytes(buffer_.getBuffer(), buffer_.length());
                if (length > 0) {
                    while (buffer_.getPosition() < length) {
                        if (header_ == 0) {
                            buffer_.readInt(header_);
                            targetLength_ = header_;
                        } else {
                            NetService::get()->addMessage(buffer_.currentPointer(), targetLength_, this);
                            buffer_.forwardPosition(targetLength_);
                            targetLength_ = kHeaderLength_;
                            header_ = 0;
                        }
                    }
                    buffer_.clear();
                    //length = ss.receiveBytes(buffer_.getBuffer(), buffer_.length());
                } else {
                    closed_ = true;
                }
            } else {
                Platform::sleep(5);
            }
        }
    } catch (Poco::Net::NetException& exc) {
        NetService::get()->onDisconnect.invoke(this);
        std::cerr << "Disconnect by remote!: " << exc.displayText() << std::endl;
    } catch (std::exception& exc) {
        std::cerr << "Disconnect by remote!: " << exc.what() << std::endl;
        NetService::get()->onDisconnect.invoke(this);
    }
}

void Connection::disconnect() {
    printf("~disconnect()\n");
    this->closed_ = true;
    if (this->valid()) {
        try {
            this->socket().shutdown();
        } catch (std::exception exc) {
            LOG_DEBUG_A(exc.what());
        }
    }
}

bool Connection::valid() const {
    return this->valid_;
}

Connection::Connection(const Poco::Net::StreamSocket& s) : TCPServerConnection(s)
    , buffer_(Default::ReceiveBufferSize)
    , targetLength_(kHeaderLength_)
    , closed_(false)
    , valid_(true) {
    this->socket().setBlocking(true);
    NetService::get()->onConnect.invoke(this);
}

Connection::~Connection() {
    printf("~Connection()\n");
    NetService::get()->onDisconnect.invoke(this);
    valid_ = false;
}


