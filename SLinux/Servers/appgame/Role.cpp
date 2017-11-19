#include "appgame.h"
#include "Role.h"
#include "TableDefine/GameRoleDefine.h"
#include "RoleSystems/SystemBase.h"
#include "RoleSystems/LevelSystem.h"
#include "RoleSystems/ItemSystem.h"
#include "RoleSystems/TaskSystem.h"
#include "RoleSystems/ChatSystem.h"
#include "RoleSystems/MailSystem.h"

Role::Role() {
    dMemoryZeroArray(this->systems_);
}


Role::~Role() {
    for (auto sys : systems_) {
        if(sys)
            sys->archieve();
        delete sys;
    }
    printf("~Role()");
}

bool Role::initialize() {
    systems_[ServerDefine::SystemType::SystemType_Level] = new LevelSystem();
    systems_[ServerDefine::SystemType::SystemType_Item] = new ItemSystem();
    systems_[ServerDefine::SystemType::SystemType_Task] = new TaskSystem();
    systems_[ServerDefine::SystemType::SystemType_Chat] = new ChatSystem();
    systems_[ServerDefine::SystemType::SystemType_Mail] = new MailSystem();
    return GameEntity::initialize();
}


void Role::createDefine() {
    this->dbInterface_ = DBService::get()->createDefine<GameRoleDefine>();
}

GameRoleDefine* Role::getDefine() const {
    return (GameRoleDefine*)this->dbInterface_;
}

void Role::syncToClient() {
    for (auto sys : systems_)
        if (sys)
            sys->initialize(this);
}

void Role::onNet(Cmd::CLIENTID id, ProtocoBuffer * pb) {
    for (auto sys : systems_)
        if (sys)
            sys->onNet(id, pb);
}
