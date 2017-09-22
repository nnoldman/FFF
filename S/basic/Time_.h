#pragma once
#include <time.h>
namespace Basic
{
class Time_
{
public:
    static double utc();
    static errno_t localTime(tm& ret);
    static std::string utcTimeString();
    static std::string localTimeString();
};
}


