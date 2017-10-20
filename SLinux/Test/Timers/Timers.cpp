#include "stdafx.h"
#include "Timers.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <assert.h>
#include <iostream>
const int64_t L0 = 256, L1 = 64, L2 = 64, L3 = 64, L4 = 64;

const int kCalcSlotIndexBase[Timers::kLevelCount] = { 0, L0 - 1, L0 + L1 - 1, L0 + L1 + L2 - 1, L0 + L1 + L2 + L3 - 1 };
const int kSlotBase[Timers::kLevelCount] = { 0, L0, L0 + L1, L0 + L1 + L2, L0 + L1 + L2 + L3 };
const int64_t kSlots[Timers::kLevelCount] = { L0, L1, L2, L3, L4 };
const int64_t kTicksInLevel[Timers::kLevelCount] = { L0, L0 * L1, L0 * L1 * L2, L0 * L1 * L2 * L3, L0 * L1 * L2 * L3 * L4 };
const int64_t kTicksPerSlot[Timers::kLevelCount] = { 1, L0, L0 * L1, L0 * L1 * L2, L0 * L1 * L2 * L3 };

Timers::Timers()
    : ticksSinceTimersStart_(0)
{
    for (auto i = 0; i < kSlotsCount; ++i)
        timers_[i] = nullptr;
    for (auto i = 0; i < kLevelCount; ++i)
        cursor_[i] = 0;
    startTime_ = currentMicroseconds();
}



Timers::~Timers()
{
    for (auto i = 0; i < kSlotsCount; ++i)
    {
        delete timers_[i];
    }
}

Timer* Timers::wait(microseconds lefttime, Timer::callback onTimerEnd /*= nullptr*/)
{
    Timer* ret = new Timer();
    ret->onEnd_ = onTimerEnd;
    if (lefttime.count() == 0)
    {
        this->cancel(ret, true);
        return nullptr;
    }
    return repeat(lefttime.count() == -1 ? microseconds(1000) : lefttime, nullptr, 1, onTimerEnd);
}

Timer* Timers::repeat(microseconds interval, Timer::callback onTimer /*= nullptr */, int  truns  /*= -1 */, Timer::callback onTimerEnd /*= nullptr */)
{
    assert(interval.count() > 0);
    assert(interval.count() % kPrecision == 0);
    assert(truns == -1 || truns  > 0);

    bool loop = truns == -1;

    Timer* ret = new Timer();
    ret->life_ = truns  * interval;
    ret->onTimer_ = onTimer;
    ret->onEnd_ = onTimerEnd;
    ret->interval_ = interval;
    ret->leftTruns_ = truns;
    ret->nextHitTicks_ = Timers::getInstance()->calcDeadTicks(ret->interval_.count());
    ret->position_ = calcSlotIndex(ret->interval_.count());

    this->addToTail(&this->timers_[ret->position_], ret);
    return ret;
}

void Timers::tick()
{
    int64_t delta = currentMicroseconds() - startTime_ - ticksSinceTimersStart_ * kPrecision;

    int count = (int)std::floor((double)delta / kPrecision);

    while (count)
    {
        ticksSinceTimersStart_++;

        int level = 0;

        while (level < kLevelCount)
        {
            int cursor = cursor_[level];
            ++cursor;
            bool change = false;
            if (cursor == kSlots[level])
            {
                cursor_[level] = 0;
                change = true;
            }
            else
            {
                cursor_[level] = cursor;
            }
            if (level == 0)
            {
                raise();
            }
            else
            {
                cascade(level);
            }
            if (!change)
            {
                break;
            }
            else
            {
                ++level;
            }
        }
        --count;
    }
}

int64_t Timers::calcDeadTicks(int64_t microseconds) const
{
    return microseconds == -1 ? -1 : ticksSinceTimersStart_ + microseconds / Timers::kPrecision;
}

int64_t Timers::currentMicroseconds() const
{
#ifdef WIN32
    return ::GetTickCount();
#endif
}

void Timers::cancel(Timer* timer, bool raiseEvent)
{
    if (timer->onEnd_ != nullptr && raiseEvent)
        timer->onEnd_(timer);
    if (timer->position_ > 0)
        this->timers_[timer->position_]->remove(timer);
    delete timer;
}

int64_t Timers::leftMicroseconds(const Timer* timer) const
{
    if (timer == nullptr)
        return -1;
    return (timer->leftTruns_ - 1) * timer->interval_.count() + (timer->nextHitTicks_ - Timers::getInstance()->currentTicks()) * Timers::kPrecision;
}

void Timers::addToTail(std::list<Timer*>** head, Timer* var)
{
    auto base = *head;
    if (base == nullptr)
    {
        base = new std::list<Timer *>();
        *head = base;
    }
    base->push_back(var);
}

int Timers::calcSlotIndex(int64_t microseconds)
{
    int64_t ticks = microseconds / kPrecision;
    assert(ticks > 0);
    int64_t offset = 0;
    int lv = 0;
    for (; lv < kLevelCount; ++lv)
    {
        if (ticks < kTicksInLevel[lv])
        {
            offset = (ticks / kTicksPerSlot[lv] + cursor_[lv]) % kSlots[lv];
            break;
        }
    }
    int ret = (int)(kCalcSlotIndexBase[lv] + offset);
    assert(ret >= 0);
    return ret;
}

void Timers::cascade(int level)
{
    assert(level >= 1 && level <= kLevelCount);
    //std::cout << "cascade:" << level << std::endl;

    int64_t base = kCalcSlotIndexBase[level] + cursor_[level];

    auto* timers = this->timers_[base];

    if (timers != nullptr)
    {
        for (auto it = timers->begin(); it != timers->end(); ++it)
        {
            auto timer = *it;
            timer->position_ = calcSlotIndex(kPrecision * (timer->nextHitTicks_ - ticksSinceTimersStart_));
            assert(base != timer->position_);
            this->addToTail(&this->timers_[timer->position_], timer);
        }
        timers->clear();
    }
}

void Timers::raise()
{
    auto base = this->cursor_[0];
    auto timers = this->timers_[base];

    if (timers != nullptr)
    {
        for (auto it = timers->begin(); it != timers->end();)
        {
            auto timer = *it;
            auto ret = processTimer(timer, base);
            if (ret & ProcessRet::Remove)
            {
                it = timers->erase(it);
                if (ret == ProcessRet::Delete)
                    delete timer;
            }
            else
            {
                ++it;
            }
        }
    }
}

Timers::ProcessRet Timers::processTimer(Timer* timer, int currentSlot)
{
    ProcessRet ret = ProcessRet::None;

    if (timer->position_ == currentSlot)
    {
        assert(timer->leftTruns_ > 0);
        if (timer->onTimer_ != nullptr)
        {
            timer->onTimer_(timer);
        }

        timer->leftTruns_--;

        if (timer->leftTruns_ == 0)
        {
            if (timer->onEnd_ != nullptr)
                timer->onEnd_(timer);
            ret = ProcessRet::Delete;
        }
        else
        {
            timer->position_ = calcSlotIndex(timer->interval_.count());
            timer->nextHitTicks_ = calcDeadTicks(timer->interval_.count());
            if (timer->position_ != currentSlot)
            {
                this->addToTail(&this->timers_[timer->position_], timer);
                ret = ProcessRet::Remove;
            }
        }
    }
    return ret;
}


API Timer* _stdcall timer_wait(int64_t microseconds, TimerCallback onTimerEnd)
{
    Timer* ret = Timers::getInstance()->wait(std::chrono::microseconds(microseconds), onTimerEnd);
    return (Timer*)ret;
}

API int64_t _stdcall timer_getLeftTime(Timer * timer)
{
    Timer* ret = (Timer*)timer;
    return ret->leftMicroseconds();
}

API void _stdcall timer_cancel(Timer* timer, bool raiseEvent)
{
    if (timer == nullptr)
        return;
    return Timers::getInstance()->cancel(timer, raiseEvent);
}

API void _stdcall timer_tick()
{
    Timers::getInstance()->tick();
}
