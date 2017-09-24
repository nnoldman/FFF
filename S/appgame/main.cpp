#include "stdafx.h"
#include "GameApp.h"
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
int main(int argc, char* argv[])
{
    GameApp app(argc, argv);
    app.run();
    return 0;
}
