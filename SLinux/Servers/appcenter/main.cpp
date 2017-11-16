#include "stdafx.h"
#include "CenterApp.h"

#ifdef WIN32
#include "vld.h"
BOOL WINAPI onControl(DWORD CtrlType) {
    if (CTRL_CLOSE_EVENT == CtrlType) {
        App::Instance->quit();
        while (App::Instance)
            Platform::sleep(5);
    }
    return TRUE;
}
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

int main(int narg, char* argv[]) {
    string exception;
    CenterApp app(narg, argv);
    app.run();
    printf(exception.c_str());
    return 0;
}

