#include "stdafx.h"
#include "World.h"
#include "App.h"
#include "DBObject.h"
#include "Connection.h"
#include "Bundle.h"


World::World()
{
}


World::~World()
{
    App::Net.onDisconnect.remove(&World::onDisconnect, this);
    dSafeDeleteMap2(accounts_);
}

bool World::initialize()
{
    App::Net.onDisconnect.add(&World::onDisconnect, this);
    BundleSender::GetInstance().onException.add(&World::onNetException, this);
    return true;
}


DBObject* World::get(Connection* connection)
{
    if (connection == nullptr)
        return nullptr;
    auto it = accounts_.find(connection);
    if (it != accounts_.end())
        return it->second;
    return nullptr;
}

const std::map<Connection*, DBObject*>& World::getAcccounts() const
{
    return this->accounts_;
}

void World::reclaimAccount(Connection* connection)
{
    if (connection == nullptr)
        return;
    //onAccountLeaveWorld.invoke(account);
    DBObject* ret = nullptr;
    if (!Basic::getValue(accounts_, connection, ret))
    {
        return;
    }
    assert(ret);
    accounts_.erase(connection);
    dSafeDelete(ret);
}

void World::onEnterWorld(Connection* connection, DBObject* account)
{
    if (account == nullptr || connection == nullptr)
        return;
    account->setConnection(connection);
    DBObject* ret = nullptr;
    Basic::getValue(accounts_, connection, ret);
    if (ret)
    {
        if (ret->globalID() != account->globalID())
        {
            dSafeDelete(ret);
            accounts_[connection] = account;
        }
    }
    else
    {
        accounts_.insert(make_pair(connection, account));
    }
    onAccountEnterWorld.invoke(account);
}


void World::onDisconnect(Connection* connection)
{
    auto ibegin = accounts_.begin();
    auto iend = accounts_.end();
    for (; ibegin != iend; ++ibegin)
    {
        if (ibegin->second->getNetInterface() == connection)
        {
            reclaimAccount(ibegin->second->getNetInterface());
            return;
        }
    }
}

void World::onNetException(Connection* connection)
{
    if (connection == nullptr)
        return;
    DBObject* ret = nullptr;
    if (Basic::getValue(accounts_, connection, ret))
    {
        auto net = ret->getNetInterface();
        net->disconnect();
    }
}
