// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <sstream>
using namespace std;

string Assert__(const char* exp, const char* file, unsigned int line);

#define AssertTrue(exp) if(!(exp)) throw new std::exception(Assert__(#exp,__FILE__,__LINE__).c_str());

// TODO: 在此处引用程序需要的其他头文件
