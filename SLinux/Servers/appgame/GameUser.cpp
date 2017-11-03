#include "stdafx.h"
#include "GameUser.h"
#include "TableDefine/GameUserDefine.h"

//ImplementObjectPoolN(GameUser, 3000);

GameUser::GameUser()
{
}


GameUser::~GameUser()
{
}

void GameUser::createDefine()
{
    this->dbInterface_ = new GameUserDefine();
}

bool GameUser::initialize()
{
    return DBObject::initialize();
}

void GameUser::onEnterGate()
{
    auto def = getDefine();
    role_.initialize();

    if (def->pull(def->id))
    {
        if (def->role > 0)
        {
            role_.setGlobalID(def->role);
            role_.getDefine()->pull(def->role);
        }
    }
    else
    {
        auto ret = def->insertAndQuery(def->id);
        assert(ret);
    }
}

Role* GameUser::getRole()
{
    return &role_;
}

void GameUser::activeRole()
{
    if (role_.valid())
    {
        role_.setConnection(getNetInterface());
        role_.syncToClient();
    }
    else
    {
        assert(false);
    }
}
