#include "stdafx.h"
#include "World.h"
#include "App.h"
#include "DBObject.h"
#include "Connection.h"


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
    return true;
}


DBObject* World::get(Connection* connection)
{
    DBObject* ret = nullptr;
    string key = connection->getSocket().address().toString();
    accounts_.Get(key, ret);
    return ret;
}

void World::reclaimAccount(Connection* connection)
{
    string key = connection->getSocket().address().toString();
    //onAccountLeaveWorld.invoke(account);
    DBObject* ret;
    accounts_.Get(key, ret);
    assert(ret);
    accounts_.erase(key);
    dSafeDelete(ret);
}

void World::onEnterWorld(Connection* connection,DBObject* account)
{
    account->setConnection(connection);
    DBObject* ret = nullptr;
    string key = connection->getSocket().address().toString();
    accounts_.Get(key, ret);
    if (ret)
    {
        if (ret->globalID() != account->globalID())
        {
            dSafeDelete(ret);
            accounts_[key] = account;
        }
    }
    else
    {
        accounts_.insert(make_pair(key, account));
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
