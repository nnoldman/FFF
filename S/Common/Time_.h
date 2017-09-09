#pragma once
#include <time.h>
namespace Basic
{
class Time_
{
public:
    static double utc();
    static errno_t localTime(tm& ret);
};
}


