#include "base.h"
#include "Time_.h"
#include <sstream>
#ifdef __GNUC__
    #include <sys/time.h>
    #include <unistd.h>
#endif
time_t Basic::Time_::utc() {
    return time(nullptr);
}

time_t Basic::Time_::local() {
    tm st;
    if (localTime(st))
        return mktime(&st);
    return 0;
}


time_t Basic::Time_::fromUTCTime(const char* time) {
    int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
    int tm_min;			/* Minutes.	[0-59] */
    int tm_hour;			/* Hours.	[0-23] */
    int tm_mday;			/* Day.		[1-31] */
    int tm_mon;			/* Month.	[0-11] */
    int tm_year;			/* Year	- 1900.  */
    //int tm_wday;			/* Day of week.	[0-6] */
    //int tm_yday;			/* Days in year.[0-365]	*/
    //int tm_isdst;			/* DST.		[-1/0/1]*/
    try {
        sscanf(time, "%d-%d-%d %d:%d:%d", &tm_year, &tm_mon, &tm_mday, &tm_hour, &tm_min, &tm_sec);
    } catch (...) {
    }
    tm st;
    dMemoryZero(&st, sizeof(tm));
    st.tm_year = tm_year - 1900;
    st.tm_mon = tm_mon - 1;
    st.tm_mday = tm_mday;
    st.tm_hour = tm_hour;
    st.tm_min = tm_min;
    st.tm_sec = tm_sec;
    return ::mktime(&st);
}


time_t Basic::Time_::fromLocalTime(const char* time) {
    time_t ret = 0;
    try {
        ret = fromUTCTime(time);
    } catch (...) {
    }
    tm st;
    if (localTime(st, &ret))
        return ::mktime(&st);
    return 0;
}


::time_t Basic::Time_::nowMinusLocalTime(const char* localTime) {
    return local() - fromLocalTime(localTime);
}

bool Basic::Time_::localTime(tm& ret, time_t* tm /*= nullptr*/) {
    const time_t t = time(nullptr);
#ifdef WIN32
    return tm == nullptr ? localtime_s(&ret, &t) != 0 : localtime_s(&ret, tm) != 0;
#elif __GNUC__
    return tm == nullptr ? localtime_r(&t, &ret) != nullptr : localtime_r(tm, &ret) != nullptr;
#endif
}

std::string Basic::Time_::utcTimeString() {
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

std::string Basic::Time_::localTimeString() {
    const time_t t = time(nullptr);
    tm ret;
#ifdef WIN32
    localtime_s(&ret, &t);
#elif __GNUC__
    localtime_r(&t, &ret);
#endif
    std::stringstream ss;
    ss << ret.tm_year + 1900 << "-" << ret.tm_mon + 1 << "-" << ret.tm_mday << " " << ret.tm_hour << ":" << ret.tm_min << ":" << ret.tm_sec;
    return ss.str();
}
int64_t Basic::Time_::getMicroSeconds() {
#if __GNUC__
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    int64_t ret = tv.tv_sec * 1000000 + tv.tv_usec;
    return ret;
#else
    return 0;
#endif
}

