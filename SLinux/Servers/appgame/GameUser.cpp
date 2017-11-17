#include "stdafx.h"
#include "GameUser.h"
#include "TableDefine/GameUserDefine.h"

//ImplementObjectPoolN(GameUser, 3000);

GameUser::GameUser() {
}


GameUser::~GameUser() {
    printf("~GameUser()");
    if (netInterface_) {
        netInterface_->disconnect();
        netInterface_ = nullptr;
    }
}

void GameUser::createDefine() {
    this->dbInterface_ = App::DataBase.createDefine<GameUserDefine>();
}

bool GameUser::initialize() {
    return DBObject::initialize();
}

void GameUser::onEnterGate() {
    auto def = getDefine();
    role_.initialize();

    if (def->pullByKey1()) {
        if (def->role > 0) {
            role_.setGlobalID(def->role);
            role_.getDefine()->pullByKey1();
        }
    } else {
        auto ret = def->insertAndQuery(def->key(), def->id);
        assert(ret);
    }
}

Role* GameUser::getRole() {
    return &role_;
}

void GameUser::activeRole() {
    if (role_.valid()) {
        role_.setConnection(getNetInterface());
        role_.syncToClient();
    } else {
        assert(false);
    }
}
