#include "appbase.h"
#include "GameEntity.h"
#include "db/DBDefine.h"

GameEntity::GameEntity()
    :dbInterface_(nullptr)
    , netInterface_(nullptr) {
    printf("DBObject():%x",this);
}

GameEntity::~GameEntity() {
    dSafeDelete(dbInterface_);
    netInterface_ = nullptr;
    printf("~DBObject():%x", this);
}
bool GameEntity::initialize() {
    this->createDefine();
    return true;
}

void GameEntity::setGlobalID(int globalID) {
    dbInterface_->id = globalID;
    globalID_ = globalID;
}

void GameEntity::syncToClient() {
}

