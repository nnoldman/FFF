// Robot.cpp : �������̨Ӧ�ó������ڵ㡣
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

