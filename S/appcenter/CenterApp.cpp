#include "stdafx.h"
#include "CenterApp.h"
#include "LoginNetAgent.h"
#include "DBTableDefine.h"
#include "GlobalRoleDefine.h"
#include "GlobalAccountDefine.h"
#include "HServer.h"

CenterApp::CenterApp(int narg, const char** args)
    : App(narg, args)
    , mNetAgent(nullptr)
    , hServer_(nullptr)
{

}

CenterApp::~CenterApp()
{
    dSafeDelete(mNetAgent);
}

const NetConfig& CenterApp::getNetConfig()
{
    return Config.login.net;
}

const DBConfig& CenterApp::getDataBaseConfig()
{
    return Config.login.db;
}

bool CenterApp::parseCommandLine()
{
    return true;
}

void CenterApp::archive()
{
}

bool CenterApp::onInitializeEnd()
{
    hServer_ = new HServer();
    hServer_->Start();
    return true;
}

bool CenterApp::onInitializeNet()
{
    mNetAgent = new LoginNetAgent();
    if (!mNetAgent->initialize())
        return false;
    return true;
}

const vector<const DBTableDefine*>& CenterApp::getTableDefines() const
{
    static const vector<const DBTableDefine*> ret
    {
        &GlobalAccountDefine::GetDefine(),
        &GlobalRoleDefine::GetDefine(),
    };
    return ret;
}

