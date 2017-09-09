#include "base.h"
#include "Time_.h"

double Basic::Time_::utc()
{
    return time(nullptr);
}

errno_t Basic::Time_::localTime(tm& ret)
{
    const time_t t = time(nullptr);
    return localtime_s(&ret, &t);
}

