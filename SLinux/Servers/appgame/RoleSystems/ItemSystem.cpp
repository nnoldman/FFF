#include "../stdafx.h"
#include "ItemSystem.h"
#include "TableDefine/GameRoleDefine.h"

ItemSystem::ItemSystem()
{
}
ItemSystem::~ItemSystem()
{
}

void ItemSystem::initialize(Role* role)
{
    SystemBase::initialize(role);
}

void ItemSystem::destroy(int dbID, GameDefine::ItemDeleteReason reason)
{
}

ItemDefine* ItemSystem::create(int itemID, GameDefine::ItemLocation location, int x)
{
    return nullptr;
}

void ItemSystem::refresh(int dbID, int count, GameDefine::ItemRefreshReason reason /*= GameDefine::ItemRefreshReason_None*/)
{

}

bool ItemSystem::sell(int dbID, GameDefine::ItemSellSource source /*= GameDefine::ItemSellSource_Invalid*/)
{
    throw new std::exception();
}

bool ItemSystem::useItem(int dbID, int num /*= 1*/)
{
    throw new std::exception();
}

bool ItemSystem::moveItem(int dbID, GameDefine::ItemLocation locationSrc, int xSrc, GameDefine::ItemLocation locationDst, int xDst)
{
    throw new std::exception();
}

