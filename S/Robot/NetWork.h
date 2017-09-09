#pragma once
#include "Poco\Net\TCPServer.h"
#include "Poco\Net\StreamSocket.h"
#include "PKG.h"
class  NetWork
{
public:
	NetWork();
	~NetWork();

	bool initialize();
	void run();
	void close();
private:
	void sendmsg(int& cnt);
	void onmsg(char* data, int len);
	Poco::Net::StreamSocket* mClient;
	int syn;
};

