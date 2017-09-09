// Robot.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NetWork.h"


int main()
{
	NetWork* work = new NetWork();
	if(work->initialize())
		work->run();
	return 0;
}

