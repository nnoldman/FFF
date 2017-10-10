#include <cstdio>
#include "Installer.h"
#include <unistd.h>
int main(int narg, char* args[])
{
	std::string name = args[0];
	auto pos = name.find_last_of('/');
	auto dir = name.substr(0, pos);
	auto ret = chdir(dir.c_str());
	Installer::run();
    return 0;
}