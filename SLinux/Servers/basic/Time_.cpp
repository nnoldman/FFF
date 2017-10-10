#include "base.h"
#include "Time_.h"
#include <sstream>

time_t Basic::Time_::utc()
{
    return time(nullptr);
}

bool Basic::Time_::localTime(tm& ret)
{
    const time_t t = time(nullptr);
#ifdef WIN32
    return localtime_s(&ret, &t) == 0;
#elif __GNUC__
    return localtime_r(&t, &ret) != nullptr;
#endif
}

std::string Basic::Time_::utcTimeString()
{
    const time_t t = time(nullptr);
    tm ret;
#ifdef WIN32
    gmtime_s(&ret, &t);
#elif __GNUC__
    gmtime_r(&t, &ret);
#endif
    std::stringstream ss;
    ss << ret.tm_year + 1900 << "-" << ret.tm_mon + 1 << "-" << ret.tm_mday << " " << ret.tm_hour << ":" << ret.tm_min << ":" << ret.tm_sec;
    return ss.str();
}

std::string Basic::Time_::localTimeString()
{
    const time_t t = time(nullptr);
    tm ret;
#ifdef WIN32
    localtime_s(&ret, &t) == 0;
#elif __GNUC__
    localtime_r(&t, &ret);
#endif
    std::stringstream ss;
    ss << ret.tm_year + 1900 << "-" << ret.tm_mon + 1 << "-" << ret.tm_mday << " " << ret.tm_hour << ":" << ret.tm_min << ":" << ret.tm_sec;
    return ss.str();
}

