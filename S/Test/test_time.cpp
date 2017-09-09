#include "stdafx.h"
#include "test_time.h"
#include <chrono>
#include <bitset>


test_time::test_time()
{
    std::chrono::system_clock::time_point nowTime = std::chrono::system_clock::now();
    __time64_t time64 = std::chrono::system_clock::to_time_t(nowTime);

    time_t tt;
    tm t;
    t.tm_year = 117;
    t.tm_mon = 9;
    t.tm_mday = 1;
    t.tm_hour = 15;
    t.tm_min = 22;
    t.tm_sec = 5;

    time_t gtime = _mkgmtime(&t);
    errno_t ret = gmtime_s(&t, &gtime);

    assert(ret == 0);
    assert(t.tm_year + 1900 == 2017);

    std::chrono::milliseconds millTime(3600000);
    std::chrono::hours hourTime(1);
    std::chrono::minutes minuteTime(60);
    std::chrono::minutes minuteTime2(30);
    std::chrono::seconds secondsTime(3600);

    assert(millTime.count() == 3600000);
    assert(hourTime.count() == 1);
    assert(minuteTime.count() == 60);
    assert(secondsTime.count() == 3600);

    assert(millTime == hourTime);
    assert(millTime == minuteTime);
    assert(millTime == secondsTime);

    minuteTime += minuteTime2;
    assert(minuteTime.count() == 90);

    minuteTime += hourTime;
    assert(minuteTime.count() == 150);

}


test_time::~test_time()
{
}
