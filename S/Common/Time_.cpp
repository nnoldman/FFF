#include "base.h"
#include "Time_.h"
#include <sstream>

double Basic::Time_::utc()
{
    return time(nullptr);
}

errno_t Basic::Time_::localTime(tm& ret)
{
    const time_t t = time(nullptr);
    return localtime_s(&ret, &t);
}

std::string Basic::Time_::utcTimeString()
{
    const time_t t = time(nullptr);
    tm ret;
    gmtime_s(&ret, &t);
    std::stringstream ss;
    ss << ret.tm_year + 1900 << "-" << ret.tm_mon + 1 << "-" << ret.tm_mday << " " << ret.tm_hour << ":" << ret.tm_min << ":" << ret.tm_sec;
    return ss.str();
}

std::string Basic::Time_::localTimeString()
{
    const time_t t = time(nullptr);
    tm ret;
    localtime_s(&ret, &t);
    std::stringstream ss;
    ss << ret.tm_year + 1900 << "-" << ret.tm_mon + 1 << "-" << ret.tm_mday << " " << ret.tm_hour << ":" << ret.tm_min << ":" << ret.tm_sec;
    return ss.str();
}

