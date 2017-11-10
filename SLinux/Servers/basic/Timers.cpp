#include "stdafx.h"
#include "Timers.h"
#ifdef WIN32
    #include <windows.h>
#endif
#include <assert.h>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace Basic
{
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
        startTime_ = currentMillseconds();
    }



    Timers::~Timers()
    {
        for (auto i = 0; i < kSlotsCount; ++i)
        {
            delete timers_[i];
        }
    }

    TimerPtr Timers::wait(int64_t lefttimeMillseconds, Timer::callback onTimerEnd /*= nullptr*/)
    {
        shared_ptr<Timer> ret(new Timer());
        ret->onEnd_ = onTimerEnd;
        if (lefttimeMillseconds == 0)
        {
            this->cancel(ret.get(), true);
            return nullptr;
        }
        return repeat(lefttimeMillseconds == -1 ? 1000 : lefttimeMillseconds, nullptr, lefttimeMillseconds, onTimerEnd);
    }

    TimerPtr Timers::repeat(int64_t intervalMillseconds, Timer::callback onTimer, int64_t leftTimeMillseconds, Timer::callback onTimerEnd)
    {
        assert(intervalMillseconds > 0);
        assert(intervalMillseconds % kPrecision == 0);
        int64_t truns = 0, mod = 0;
        if (leftTimeMillseconds < 0)
        {
            truns = -1;
        }
        else
        {
            assert(leftTimeMillseconds % kPrecision == 0);
            truns = leftTimeMillseconds / intervalMillseconds;
            mod = leftTimeMillseconds % intervalMillseconds;
            if (mod > 0)
                truns++;
        }
        std::shared_ptr<Timer> ret(new Timer());
        ret->lifeMillseconds_ = leftTimeMillseconds;
        ret->onTimer_ = onTimer;
        ret->onEnd_ = onTimerEnd;
        ret->intervalMillseconds_ = intervalMillseconds;
        ret->leftTruns_ = truns;
        //×Ô¶¯ÑÓÊ±
        if (mod > 0)
        {
            ret->nextHitTicks_ = Timers::getInstance()->calcDeadTicks(mod);
            ret->position_ = calcSlotIndex(mod);
        }
        else
        {
            ret->nextHitTicks_ = Timers::getInstance()->calcDeadTicks(ret->intervalMillseconds_);
            ret->position_ = calcSlotIndex(ret->intervalMillseconds_);
        }
        this->addToTail(&this->timers_[ret->position_], ret);
        return ret;
    }

    void Timers::tick()
    {
        int64_t delta = currentMillseconds() - startTime_ - ticksSinceTimersStart_ * kPrecision;
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

    int64_t Timers::currentMillseconds() const
    {
        auto clock = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(clock.time_since_epoch());
        return now.count();
    }

    void Timers::cancel(Timer* timer, bool raiseEvent)
    {
        if (timer->onEnd_ != nullptr && raiseEvent)
            timer->onEnd_(timer);
        if (timer->position_ > 0)
        {
            auto timers = this->timers_[timer->position_];
            assert(timers != nullptr);
            auto it = std::find_if(timers->begin(), timers->end(), [timer](const TimerPtr it)
            {
                return timer == it.get();
            });
            assert(it != timers->end());
            timers->erase(it);
            delete timer;
        }
    }

    int64_t Timers::leftMicroseconds(const Timer* timer) const
    {
        if (timer == nullptr)
            return -1;
        return timer->leftTruns_ == 0 ? 0 : (timer->leftTruns_ - 1) * timer->intervalMillseconds_
               + (timer->nextHitTicks_ - Timers::getInstance()->currentTicks()) * Timers::kPrecision;
    }

    void Timers::addToTail(std::list<TimerPtr>** head, TimerPtr var)
    {
        auto base = *head;
        if (base == nullptr)
        {
            base = new std::list<TimerPtr>();
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
                        delete timer.get();
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    Timers::ProcessRet Timers::processTimer(TimerPtr timer, int currentSlot)
    {
        ProcessRet ret = ProcessRet::None;
        if (timer->position_ == currentSlot)
        {
            assert(timer->leftTruns_ > 0);
            if (timer->onTimer_ != nullptr)
            {
                timer->onTimer_(timer.get());
            }
            timer->leftTruns_--;
            if (timer->leftTruns_ == 0)
            {
                if (timer->onEnd_ != nullptr)
                    timer->onEnd_(timer.get());
                ret = ProcessRet::Delete;
            }
            else
            {
                timer->position_ = calcSlotIndex(timer->intervalMillseconds_);
                timer->nextHitTicks_ = calcDeadTicks(timer->intervalMillseconds_);
                if (timer->position_ != currentSlot)
                {
                    this->addToTail(&this->timers_[timer->position_], timer);
                    ret = ProcessRet::Remove;
                }
            }
        }
        return ret;
    }

#ifdef WIN32
    CAPI Timer* stdcall timer_wait(int64_t millseconds, TimerCallback onTimerEnd)
#elif __GNUC__
    Timer* timer_wait(int64_t millseconds, TimerCallback onTimerEnd)
#endif
    {
        auto ret = Timers::getInstance()->wait(millseconds, onTimerEnd);
        return ret.get();
    }

#ifdef WIN32
    CAPI int64_t stdcall timer_getLeftTime(Timer * timer)
#elif __GNUC__
    int64_t  timer_getLeftTime(Timer * timer)
#endif
    {
        Timer* ret = (Timer*)timer;
        return ret->leftMillseconds();
    }

#ifdef WIN32
    CAPI void stdcall timer_cancel(Timer* timer, bool raiseEvent)
#elif __GNUC__
    void  timer_cancel(Timer* timer, bool raiseEvent)
#endif
    {
        if (timer == nullptr)
            return;
        return Timers::getInstance()->cancel(timer, raiseEvent);
    }

#ifdef WIN32
    CAPI void stdcall timer_tick()
#elif __GNUC__
    void  timer_tick()
#endif
    {
        Timers::getInstance()->tick();
    }

}
