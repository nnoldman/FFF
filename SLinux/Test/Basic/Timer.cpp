#include "base.h"
#include "Timer.h"
#include "Timers.h"
#include <iostream>
#include <assert.h>

namespace Basic {
    Timer::Timer()
        : onTimer_(nullptr)
        , onEnd_(nullptr)
        , lifeMillseconds_(0)
        , intervalMillseconds_(0)
        , nextHitTicks_(0)
        , leftTruns_(0)
        , position_(-1)
    {
    }


    Timer::~Timer()
    {
        std::cout << "Timer>>" << lifeMillseconds_ << std::endl;
    }

    void Timer::cancel(bool raise /*= false*/)
    {
        Timers::getInstance()->cancel(this, raise);
    }

    int64_t Timer::leftMillseconds() const
    {
        return Timers::getInstance()->leftMicroseconds(this);
    }

    int Timer::leftSeconds() const
    {
        return (int)(leftMillseconds() * 0.001);
    }

    std::chrono::milliseconds Timer::life() const
    {
        return milliseconds(this->lifeMillseconds_);
    }
}