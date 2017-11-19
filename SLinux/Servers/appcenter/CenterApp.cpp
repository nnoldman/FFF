#include "appcenter.h"
#include "CenterApp.h"
#include "CenterNetService.h"
#include "GlobalRoleDefine.h"
#include "GlobalAccountDefine.h"
#include "HttpService.h"

CenterApp::CenterApp(int narg, char* argv[])
    : App(narg, argv) {
}

CenterApp::~CenterApp() {
}

void CenterApp::archive() {
}

void CenterApp::addExternServices() {
    addController<CenterNetService>();
    addController<HttpService>();
}
const vector<const DBTableDefine*>& CenterApp::getTableDefines() const {
    static const vector<const DBTableDefine*> ret {
        &GlobalAccountDefine::GetDefine(),
        &GlobalRoleDefine::GetDefine(),
    };
    return ret;
}

