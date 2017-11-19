#include "../appbase.h"
#include "NetService.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/NetException.h"
#include "../net/Bundle.h"
#include "OptionService.h"

NetService::NetService() {
}

NetService::~NetService() {
    dSafeDeleteVector(mDataArray);
    if (mServer) {
        mServer->stop();
        dSafeDelete(mServer);
    }
}

bool NetService::initialize(const NetOption& config) {
    Net::TCPServerParams::Ptr params = new Net::TCPServerParams();
    params->setMaxThreads(config.threadCount);
    mServer = new Poco::Net::TCPServer(new Net::TCPServerConnectionFactoryImpl<Connection>()
                                       , config.port, params);
    mServer->start();
    return true;
}

void NetService::tick() {
    mLock.lock();
    Array<Packet*> pktArray;
    for (int i = 0; i < mDataArray.size(); ++i) {
        Packet* pkt = mDataArray[i];
        pktArray.push_back(pkt);
    }

    mDataArray.clear();
    mLock.unlock();

    for (int i = 0; i < pktArray.size(); ++i) {
        Packet* pkt = pktArray[i];
        BundleReceiver bundle(pkt->con, pkt->data, pkt->len);
        if (bundle.valid()) {
            ProtocoBuffer* pkg = bundle.get();
            this->onMessage.invoke(pkg, pkt->con);
        }
        dSafeDelete(pkt);
    }
    pktArray.clear();
}

void NetService::addMessage(void* data, u32 len, Connection* con) {
    mLock.lock();
    Packet* pkt = new Packet();
    pkt->data = new char[len];
    pkt->len = len;
    pkt->con = con;
    dMemoryCopy(pkt->data, data, len);
    mDataArray.push_back(pkt);
    mLock.unlock();
}

bool NetService::start() {
    if (!OptionService::get()->getOption(ServerID::get().c_str(), "net", option_))
        return false;
    if (!initialize(option_))
        return false;
    return true;
}

const char * NetService::name() {
    return "NetService";
}

