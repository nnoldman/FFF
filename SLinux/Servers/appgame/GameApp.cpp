#include "appgame.h"
#include "GameApp.h"
#include "GameNetAgent.h"
#include "TableDefine/GameUserDefine.h"
#include "TableDefine/GameRoleDefine.h"
#include "Config/TimeTable.h"
#include "Config/Language.h"
#include "GameSystems/ControllerService.h"
#include "TableDefine/ItemDefine.h"
#include "Config/ItemTable.h"
#include "TableDefine/MailDefine.h"

GameApp::GameApp(int argc, char* argv[])
    : App(argc, argv) {
}

GameApp::~GameApp() {
}

void GameApp::archive() {
}

const vector<const DBTableDefine*>& GameApp::getTableDefines() const {
    static const vector<const DBTableDefine*> ret {
        &GameUserDefine::GetDefine(),
        &GameRoleDefine::GetDefine(),
        &ItemDefine::GetDefine(),
        &MailDefine::GetDefine(),
    };
    return ret;
}

bool GameApp::loadGameConfig() {
    TimeTable::getInstance()->reload();
    ItemTable::getInstance()->reload();
    Language::getInstance()->reload();
    return true;
}

void GameApp::mainLoop() {
    App::mainLoop();
}

void GameApp::addExternServices() {
    addController<GameNetAgent>();
    addController<ControllerService>();
}
