#include "Installer.h"
#include <cstdio>

std::map<std::string, function> Installer::functions_;

void Installer::add(const char* name, function func)
{
	functions_.insert(std::make_pair(name, func));
}

void Installer::run()
{
	for (auto it : functions_)
	{
		try
		{
			it.second();

			std::cout << std::endl << "Sucessed: " << it.first.c_str();
		}
		catch (std::exception exc)
		{
			std::cout << exc.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Failed: " << it.first.c_str() << std::endl;
		}
	}
}
