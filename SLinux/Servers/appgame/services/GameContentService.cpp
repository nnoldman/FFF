#include "../appgame.h"
#include "GameContentService.h"
#include "Config/TimeTable.h"
#include "Config/Language.h"
#include "Config/ItemTable.h"


GameContentService::GameContentService() {
    this->dynamic_ = false;
}

GameContentService::~GameContentService() {
}


bool GameContentService::start() {
    TimeTable::getInstance()->reload();
    ItemTable::getInstance()->reload();
    Language::getInstance()->reload();
    return true;
}

const char * GameContentService::name() {
    return "GameContentService";
}
