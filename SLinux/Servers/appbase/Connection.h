#pragma once
#include "Poco/Net/TCPServerConnection.h"
#include "ProtocoBuffer.h"
class COREAPI Connection : public Poco::Net::TCPServerConnection
{
public:
    Connection(const Poco::Net::StreamSocket& s);

    ~Connection();

    void run();

    inline Poco::Net::StreamSocket& getSocket();

    void disconnect();

	bool valid() const;
private:
    Basic::Buffer buffer_;
    int targetLength_;
    int header_ = 0;
    bool closed_;
	bool valid_;
};
inline Poco::Net::StreamSocket& Connection::getSocket()
{
    return socket();
}
