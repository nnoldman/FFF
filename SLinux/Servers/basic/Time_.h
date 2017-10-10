#pragma once
#include <time.h>
namespace Basic
{
    class Time_
    {
    public:
        static time_t utc();
        static bool localTime(tm& ret);
        static std::string utcTimeString();
        static std::string localTimeString();
    };
}


