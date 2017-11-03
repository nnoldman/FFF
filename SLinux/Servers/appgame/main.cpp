#include "stdafx.h"
#include "GameApp.h"
#include "App.h"
#include "Poco/File.h"
#include "TableDefine/GameRoleDefine.h"

#ifdef WIN32
    #pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif


int main(int argc, char* argv[])
{
    printf("ROLE DEFINE SIZE:%d B\n", sizeof(GameRoleDefine));
    GameApp app(argc, argv);
    app.run();
    return 0;
}
