// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

//#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <iostream>
#include <sstream>
#include "Basic.h"
#include "Poco\Dynamic\Var.h"
#include "Poco\Net\NetException.h"
using namespace Poco;
using namespace Poco::Net;
#include "Default.h"
#include "uString.h"
using namespace Basic;
typedef std::vector<std::string> stringVector;
typedef std::vector<stringVector> stringVectorVector;

#define LOG_CRITICAL_A(...)
#define LOG_DEBUG_A(...)
#define LOG_ERROR_A(...)
#define LOG_FATAL_A(...)
#define LOG_INFO_A(...)
#define LOG_NOTICE_A(...)
#define LOG_TRACE_A(...)
#define LOG_WARNING_A(...)

//#define LOG_CRITICAL_A(...) Poco::Util::Application::instance().logger().critical(__VA_ARGS__)
//#define LOG_DEBUG_A(...) Poco::Util::Application::instance().logger().debug(__VA_ARGS__)
//#define LOG_ERROR_A(...) Poco::Util::Application::instance().logger().error(__VA_ARGS__)
//#define LOG_FATAL_A(...) Poco::Util::Application::instance().logger().fatal(__VA_ARGS__)
//#define LOG_INFO_A(...) Poco::Util::Application::instance().logger().information(__VA_ARGS__)
//#define LOG_NOTICE_A(...) Poco::Util::Application::instance().logger().notice(__VA_ARGS__)
//#define LOG_TRACE_A(...) Poco::Util::Application::instance().logger().trace(__VA_ARGS__)
//#define LOG_WARNING_A(...) Poco::Util::Application::instance().logger().warning(__VA_ARGS__)