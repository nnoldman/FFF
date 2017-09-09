#include "stdafx.h"
#include "GameApp.h"
#include "CenterNetAgent.h"
#include "GameUserDefine.h"
#include "GameRoleDefine.h"

GameApp::GameApp(int narg, const char** args)
    : App(narg, args)
    , netAgent_(nullptr)
{

}

GameApp::~GameApp()
{
    dSafeDelete(netAgent_);
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
    };
    return ret;
}
