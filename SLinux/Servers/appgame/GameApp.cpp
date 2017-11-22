#include "appgame.h"
#include "GameApp.h"
#include "services/GameNetAgent.h"
#include "services/GameContentService.h"

#include "GameSystems/ControllerService.h"

#include "TableDefine/GameUserDefine.h"
#include "TableDefine/GameRoleDefine.h"
#include "TableDefine/ItemDefine.h"
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

void GameApp::mainLoop() {
    App::mainLoop();
}

void GameApp::addExternServices() {
    addController<GameNetAgent>();
    addController<GameContentService>();
    addController<ControllerService>();
}
