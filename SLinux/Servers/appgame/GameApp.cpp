#include "stdafx.h"
#include "GameApp.h"
#include "CenterNetAgent.h"
#include "TableDefine/GameUserDefine.h"
#include "TableDefine/GameRoleDefine.h"
#include "Config/TimeTable.h"
#include "Config/Language.h"
#include "GameSystems/GameControllers.h"
#include "TableDefine/ItemDefine.h"
#include "Config/ItemTable.h"

GameApp::GameApp(int argc, char* argv[])
    : App(argc, argv)
    , netAgent_(nullptr)
    , controllers_(nullptr)
{
}

GameApp::~GameApp()
{
    dSafeDelete(netAgent_);
    dSafeDelete(controllers_);
}

const NetConfig& GameApp::getNetConfig()
{
    return *Config.center.centers[serverID_];
}

const DBConfig& GameApp::getDataBaseConfig()
{
    return Config.center.db;
}

bool GameApp::parseCommandLine()
{
    auto commandline = this->getCommandLine();
    commandline.get("serverID", serverID_);
    string serverID;
    commandline.get("serverID", serverID);
    ServerID::set(serverID.c_str());
    return serverID_ > 0;
}

void GameApp::archive()
{
}
bool GameApp::onInitializeEnd()
{
    controllers_ = new GameControllers();
    controllers_->start();
    return true;
}

bool GameApp::onInitializeNet()
{
    netAgent_ = new CenterNetAgent();
    netAgent_->initialize();
    return true;
}

const vector<const DBTableDefine*>& GameApp::getTableDefines() const
{
    static const vector<const DBTableDefine*> ret
    {
        &GameUserDefine::GetDefine(),
        &GameRoleDefine::GetDefine(),
        &ItemDefine::GetDefine(),
    };
    return ret;
}

bool GameApp::loadGameConfig()
{
    TimeTable::getInstance()->reload();
    ItemTable::getInstance()->reload();
    Language::getInstance()->reload();
    return true;
}

void GameApp::mainLoop()
{
    App::mainLoop();
    controllers_->update();
}
