#include "stdafx.h"
#include "GameApp.h"
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
int main(int argc, const char** argv)
{
    GameApp* app = new GameApp(argc, argv);
    return App::Main(app);
}
