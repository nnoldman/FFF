#include "stdafx.h"
#include "Timer.h"
#include "Timers.h"
#include <iostream>
#include <assert.h>


Timer::Timer()
    : onTimer_(nullptr)
    , onEnd_(nullptr)
    , life_(0)
    , interval_(0)
    , position_(-1)
    , nextHitTicks_(0)
    , leftTruns_(0)
{
}


Timer::~Timer()
{
    std::cout << "Timer>>" << life_.count() << std::endl;
}

void Timer::cancel(bool raise /*= false*/)
{

}

int64_t Timer::leftMicroseconds() const
{
    return Timers::getInstance()->leftMicroseconds(this);
}

std::chrono::microseconds Timer::life() const
{
    return this->life_;
}
