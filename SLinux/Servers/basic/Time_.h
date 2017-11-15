#pragma once
#include <time.h>
namespace Basic {
    class Time_ {
      public:
        static time_t utc();
        static time_t local();
        static time_t fromUTCTime(const char* time);
        static time_t fromLocalTime(const char* time);
        static time_t nowMinusLocalTime(const char* localTime);
        static bool localTime(tm& ret, time_t* tm = nullptr);
        static std::string utcTimeString();
        static std::string localTimeString();
        static int64_t getMicroSeconds();
    };
}


