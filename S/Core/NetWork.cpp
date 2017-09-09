#include "stdafx.h"
#include "NetWork.h"
#include "ConfigInfo.h"
#include "Poco\Net\TCPServerConnection.h"
#include "Poco\Net\StreamSocket.h"
#include "Poco\Net\TCPServerConnectionFactory.h"
#include "App.h"
#include "Bundle.h"
#include "Poco\Net\NetException.h"

NetWork::NetWork()
{
}


NetWork::~NetWork()
{
    dSafeDeleteVector(mDataArray);
    if (mServer)
    {
        mServer->stop();
        dSafeDelete(mServer);
    }
}

bool NetWork::initialize(const NetConfig& config)
{
    Net::TCPServerParams::Ptr params = new Net::TCPServerParams();
    params->setMaxThreads(config.threadCount);
    mServer = new Poco::Net::TCPServer(new Net::TCPServerConnectionFactoryImpl<Connection>()
                                       , config.port, params);
    mServer->start();
    return true;
}

void NetWork::prosess()
{
    mLock.lock();
    Array<Packet*> pktArray;
    for (int i = 0; i < mDataArray.size(); ++i)
    {
        Packet* pkt = mDataArray[i];
        pktArray.push_back(pkt);
    }

    mDataArray.clear();
    mLock.unlock();

    for (int i = 0; i < pktArray.size(); ++i)
    {
        Packet* pkt = pktArray[i];
        BundleReceiver bundle(pkt->con, pkt->data, pkt->len);
        if (bundle.valid())
        {
            ProtocoBuffer* pkg = bundle.get();
            App::Net.onMessage.invoke(pkg, pkt->con);
        }
        dSafeDelete(pkt);
    }
    pktArray.clear();
}

void NetWork::addMessage(void* data, u32 len, Connection* con)
{
    mLock.lock();
    Packet* pkt = new Packet();
    pkt->data = new char[len];
    pkt->len = len;
    pkt->con = con;
    dMemoryCopy(pkt->data, data, len);
    mDataArray.push_back(pkt);
    mLock.unlock();
}

