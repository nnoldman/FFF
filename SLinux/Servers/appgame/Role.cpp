#include "stdafx.h"
#include "Role.h"
#include "TableDefine/GameRoleDefine.h"
#include "RoleSystems/SystemBase.h"
#include "RoleSystems/LevelSystem.h"
#include "RoleSystems/ItemSystem.h"
#include "RoleSystems/TaskSystem.h"

Role::Role()
{
}


Role::~Role()
{
    for (auto sys : systems_)
    {
        sys->archieve();
        delete sys;
    }
}

bool Role::initialize()
{
    systems_[ServerDefine::SystemType::SystemType_Level] = new LevelSystem();
    systems_[ServerDefine::SystemType::SystemType_Item] = new ItemSystem();
    systems_[ServerDefine::SystemType::SystemType_Task] = new TaskSystem();
    return DBObject::initialize();
}

void Role::createDefine()
{
    this->dbInterface_ = new GameRoleDefine();
}

GameRoleDefine* Role::getDefine() const
{
    return (GameRoleDefine*)this->dbInterface_;
}

void Role::syncToClient()
{
    for (auto sys : systems_)
        sys->initialize(this);
}

void Role::onNet(Cmd::CLIENTID id, ProtocoBuffer * pb)
{
    for (auto sys : systems_)
        sys->onNet(id, pb);
}
