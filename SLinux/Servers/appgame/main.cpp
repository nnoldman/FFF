#include "stdafx.h"
#include "GameApp.h"
#include "App.h"
#include "Poco/File.h"

#ifdef WIN32
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif


int main(int argc, char* argv[])
{
	GameApp app(argc, argv);
	app.run();

	return 0;
}
