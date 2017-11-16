// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

//#include "targetver.h"

#include <stdio.h>
#ifdef WIN32
    #include <tchar.h>
#endif



// TODO:  在此处引用程序需要的其他头文件
#include <iostream>
#include <sstream>
#include <typeinfo>

#include "Basic.h"
#include "Poco/Net/Socket.h"
#include "Poco/Util/Application.h"
#include "Poco/Logger.h"
#include "Default.h"

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;
using namespace Basic;

//#define LOG_CRITICAL_A(...)
//#define LOG_DEBUG_A(...)
//#define LOG _ERROR_A(...)
//#define LOG_FATAL_A(...)
//#define LOG_INFO_A(...)
//#define LOG_NOTICE_A(...)
//#define LOG_TRACE_A(...)
//#define LOG_WARNING_A(...)

#define LOG_CRITICAL_A(...) Poco::Util::Application::instance().logger().critical(__VA_ARGS__)
#define LOG_DEBUG_A(...) Poco::Util::Application::instance().logger().debug(__VA_ARGS__)
#define LOG_ERROR_A(...) Poco::Util::Application::instance().logger().error(__VA_ARGS__)
#define LOG_FATAL_A(...) Poco::Util::Application::instance().logger().fatal(__VA_ARGS__)
#define LOG_INFO_A(...) Poco::Util::Application::instance().logger().information(__VA_ARGS__)
#define LOG_NOTICE_A(...) Poco::Util::Application::instance().logger().notice(__VA_ARGS__)
#define LOG_TRACE_A(...) Poco::Util::Application::instance().logger().trace(__VA_ARGS__)
#define LOG_WARNING_A(...) Poco::Util::Application::instance().logger().warning(__VA_ARGS__)

#define FORMAT_TEXT(buffer,fmt,...) char buffer[2048] = {0};\
    snprintf(buffer, 2048, fmt, __VA_ARGS__);
