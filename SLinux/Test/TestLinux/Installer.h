#pragma once
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <assert.h>
typedef void(*function)();
class Installer
{
public:
	static void add(const char* name,function func);
	static void run();
private:
	static std::map<std::string,function> functions_;
};

#define Function(name) \
void name();\
class name##_Test\
{\
public:\
	name##_Test()\
	{\
		Installer::add(#name,name);\
	}\
}g_##name##_Test;\
void name()

