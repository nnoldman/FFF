#include "stdafx.h"
#include "GameApp.h"
#include "App.h"
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

BOOL CtrlHandler(DWORD fdwCtrlType);

int main(int argc, char* argv[])
{
    GameApp app(argc, argv);
    app.run();
    return 0;
}

BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    /* handle the CTRL-C signal */
    case CTRL_C_EVENT:
        printf("CTRL-C event\n");
        Beep(750, 300);
        return TRUE;

    /* handle the CTRL-BREAK signal */
    case CTRL_BREAK_EVENT:
        printf("CTRL-BREAK event\n");
        Beep(900, 200);
        App::Instance->quit();
        return TRUE;

    /* handle the CTRL-CLOSE signal */
    case CTRL_CLOSE_EVENT:
        printf("点击了控制台右上角的“X”\n");
        Beep(600, 200);
        return TRUE;

    /* handle the CTRL-LOGOFF signal */
    case CTRL_LOGOFF_EVENT:
        printf("CTRL-LOGOFF event\n");
        Beep(1000, 200);
        return TRUE;

    /* handle the CTRL-SHUTDOWN signal */
    case CTRL_SHUTDOWN_EVENT:
        printf("CTRL-SHUTDOWN event\n");
        Beep(750, 500);
        return TRUE;

    default:
        return FALSE;
    }
}
