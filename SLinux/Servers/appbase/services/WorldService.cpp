#include "../appbase.h"
#include "WorldService.h"
#include "NetService.h"
#include "../GameEntity.h"
#include "../net/Connection.h"
#include "../net/Bundle.h"


WorldService::WorldService()
    : dirty_(false) {
}


WorldService::~WorldService() {
    NetService::get()->onDisconnect.remove(&WorldService::onDisconnect, this);
    dSafeDeleteMap2(accounts_);
}

bool WorldService::start() {
    NetService::get()->onDisconnect.add(&WorldService::onDisconnect, this);
    BundleSender::GetInstance().onException.add(&WorldService::onNetException, this);
    return true;
}


GameEntity* WorldService::getAccount(Connection* connection) {
    if (connection == nullptr)
        return nullptr;
    auto it = accounts_.find(connection);
    if (it != accounts_.end())
        return it->second;
    return nullptr;
}

const std::map<Connection*, GameEntity*>& WorldService::getAcccounts() const {
    return this->accounts_;
}
void WorldService::process() {
    if (!this->dirty_)
        return;
    for (auto it : this->quitedAccounts_) {
        GameEntity* ret = nullptr;
        if (!Basic::getValue(accounts_, it, ret)) {
            assert(false);
            return;
        }
        accounts_.erase(it);
        dSafeDelete(ret);
    }
    this->quitedAccounts_.clear();
    this->dirty_ = false;
}
void WorldService::reclaimAccount(Connection* connection) {
    if (connection == nullptr)
        return;
    //onAccountLeaveWorld.invoke(account);
    GameEntity* ret = nullptr;
    if (!Basic::getValue(accounts_, connection, ret)) {
        return;
    }
    if(std::find(this->quitedAccounts_.begin(), this->quitedAccounts_.end(), connection) == this->quitedAccounts_.end())
        this->quitedAccounts_.push_back(connection);
    this->dirty_ = true;
    //assert(ret);
    //accounts_.erase(connection);
    //dSafeDelete(ret);
}

void WorldService::onEnterWorld(Connection* connection, GameEntity* account) {
    if (account == nullptr || connection == nullptr)
        return;
    account->setConnection(connection);
    GameEntity* ret = nullptr;
    Basic::getValue(accounts_, connection, ret);
    if (ret) {
        if (ret->globalID() != account->globalID()) {
            dSafeDelete(ret);
            accounts_[connection] = account;
        }
    } else {
        accounts_.insert(make_pair(connection, account));
    }
    onAccountEnterWorld.invoke(account);
}


void WorldService::onDisconnect(Connection* connection) {
    auto ibegin = accounts_.begin();
    auto iend = accounts_.end();
    for (; ibegin != iend; ++ibegin) {
        if (ibegin->second->getNetInterface() == connection) {
            reclaimAccount(ibegin->second->getNetInterface());
            return;
        }
    }
}

void WorldService::onNetException(Connection* connection) {
    if (connection == nullptr)
        return;
    GameEntity* ret = nullptr;
    if (Basic::getValue(accounts_, connection, ret)) {
        auto net = ret->getNetInterface();
        net->disconnect();
    }
}

const char * WorldService::name() {
    return "WorldService";
}
