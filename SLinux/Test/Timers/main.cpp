#include "stdafx.h"
#include "Timer.h"
#include "Timers.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <functional>
Timer* pTimer = nullptr;
int count = 0;

int64_t PreTime = 0;

void OnTimerEnd(Timer* timer)
{
    std::cout << "OnTimerEnd:" << timer->leftMicroseconds() << std::endl;
    std::cout << "OnTimerEnd:" << timer->life().count() << std::endl;
}
void OnTimer(Timer* timer)
{
    std::cout << "OnTimer:" << timer->leftMicroseconds() / 1000 << std::endl;
}

class System
{
private:
    int id = 5;
public:
    ~System()
    {
        id = 0;
    }
public:
    void OnTimerEnd(Timer* timer)
    {
        std::cout << "OnTimerEnd:" << timer->leftMicroseconds() << std::endl;
        std::cout << "OnTimerEnd:" << timer->life().count() << std::endl;
    }
public:
    static void OnTimerEnd2(Timer* timer)
    {
        std::cout << "OnTimerEnd:" << timer->leftMicroseconds() << std::endl;
        std::cout << "OnTimerEnd:" << timer->life().count() << std::endl;
    }
    void OnTimer(Timer* timer)
    {
        std::cout << "OnTimer:" << timer->leftMicroseconds() / 1000 << std::endl;
    }
};

int main()
{
    //std::ofstream ofs("log.txt");
    //std::streambuf *strmout_buf = std::cout.rdbuf();
    //std::cout.rdbuf(ofs.rdbuf());
    if (1)
    {
        auto sys = new System();
        pTimer = Timers::getInstance()->wait(microseconds(3000), &System::OnTimerEnd, sys);
        pTimer = Timers::getInstance()->wait(microseconds(3000), &System::OnTimerEnd2);
        pTimer = Timers::getInstance()->wait(microseconds(5000), ::OnTimerEnd);
        //delete sys;
    }
    else if (0)
    {
        pTimer = Timers::getInstance()->repeat(microseconds(1000), OnTimer, 3600, OnTimerEnd);
        pTimer = Timers::getInstance()->wait(microseconds(3600 * 1000), OnTimerEnd);
    }
    else if (0)
    {
        int slot = 0, base = 0;

        base = 0;
        slot = 10;

        //pTimer = Timers::getInstance()->wait(microseconds(10), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 10 / slot);
        //pTimer = Timers::getInstance()->wait(microseconds(20), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 20 / slot);

        //pTimer = Timers::getInstance()->wait(microseconds(2550), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 2550 / slot);

        base = 255;
        slot = 2560;

        //pTimer = Timers::getInstance()->wait(microseconds(2560), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 2560 / slot);

        pTimer = Timers::getInstance()->wait(microseconds(5110), OnTimerEnd);
        assert(pTimer->nextHitTicks() == base + 5110 / slot);

        //pTimer = Timers::getInstance()->wait(microseconds(5120), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 5120 / slot);

        //pTimer = Timers::getInstance()->wait(microseconds(256 * 63 * 10), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 256 * 63 * 10 / slot);

        //base = 319;
        //slot = 256 * 64 * 10;

        //pTimer = Timers::getInstance()->wait(microseconds(256 * 64 * 10), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + 256 * 64 * 10 / slot);

        //pTimer = Timers::getInstance()->wait(microseconds(256 * 64 * 10 + 10), OnTimerEnd);
        //assert(pTimer->getEndSlot() == base + (256 * 64 * 10 + 10) / slot);
        ////pTimer = Timers::getInstance()->wait(microseconds(163820), OnTimerEnd);
        ////pTimer = Timers::getInstance()->wait(microseconds(163830), OnTimerEnd);
        ////pTimer = Timers::getInstance()->wait(microseconds(163840), OnTimerEnd);
        //pTimer = Timers::getInstance()->wait(microseconds(330230), OnTimerEnd);
    }
    else if (0)
    {
        for (int i = 1; i < 5000; ++i)
        {
            //Timers::getInstance()->wait(microseconds(i * 10), OnTimerEnd);
            pTimer = Timers::getInstance()->repeat(microseconds(1000), OnTimer, i, OnTimerEnd);
        }
    }

    PreTime = Timers::getInstance()->currentMicroseconds();

    while (true)
    {
        //std::cout << "============" << pTimer->getLeftMicroseconds() << std::endl;
        Timers::getInstance()->tick();
        ::Sleep(10);
    }
    return 0;
}