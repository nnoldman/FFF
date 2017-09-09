#include "stdafx.h"
#include "NetWork.h"
#include "Poco\Net\TCPServerConnection.h"
#include "Poco\Net\StreamSocket.h"
#include "Poco\Net\TCPServerConnectionFactory.h"
#include "Poco\Exception.h"
#include "PKG\PKG.h"
#include "Bundle.h"



NetWork::NetWork()
	:mClient(nullptr)
{
}


NetWork::~NetWork()
{
	if (mClient)
		mClient->close();
	delete mClient;
}

bool NetWork::initialize()
{
	mClient = new Poco::Net::StreamSocket();
	try
	{
		mClient->connect(Poco::Net::SocketAddress("localhost", 15299));
	}
	catch (Poco::Exception e)
	{
		printf(e.message().c_str());
		close();
		return false;
	}
	return true;
}

static int msgCount = 0;

void NetWork::run()
{
	PKGSYN syn;
	this->syn = syn.key;
	SendPKG(*mClient, syn);

	uBuffer buffer(512);
	try
	{
		int n = mClient->receiveBytes(buffer.getPointer(), buffer.capacity());
		while (n > 0)
		{
			onmsg(buffer.getPointer(), n);
			buffer.clear();
			n = mClient->receiveBytes(buffer.getPointer(), buffer.capacity());
		}
	}
	catch (Poco::IOException e)
	{
		printf("断开连接。。");
	}

}

void NetWork::close()
{
	if (mClient)
		mClient->close();
	dSafeDelete(mClient);
}


void NetWork::sendmsg(int& cnt)
{
	uString msg;
	msg.format("Hello%d\n", cnt);
	printf(msg.c_str());
	mClient->sendBytes(msg.c_str(), msg.sizeOfByte());
}

void NetWork::onmsg(char* data, int len)
{
	BundleReceiver bundle(mClient, data, len);
	if (bundle.valid())
	{
		PKG* pkg = bundle.get();
		printf("(PKG:%d)\n", pkg->code);
		switch (pkg->code)
		{
		case PCODE::ACK:
		{
			PKGACK* ack = (PKGACK*)pkg;
			if (ack->key == this->syn + 1)
			{
				printf("连接成功！");
			}

			rqCreateAccount rq;
			//rq.id = 0351;
			SendPKG(*mClient, rq);
		}
		break;
		case PCODE::SYN:
		{
			PKGSYN* syn = (PKGSYN*)pkg;
			PKGACK ack;
			ack.key = syn->key + 1;
			SendPKG(*mClient, ack);
		}
		break;
		}
		delete pkg;
	}
}
