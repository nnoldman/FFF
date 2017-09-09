#include "stdafx.h"
#include "Role.h"
#include "GameRoleDefine.h"

Role::Role()
{
}


Role::~Role()
{
}

bool Role::initialize()
{
    return __super::initialize();
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
}
