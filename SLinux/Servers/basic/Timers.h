#ifndef Timers_h__
#define Timers_h__
#include <list>
#include <chrono>
#include "Timer.h"
#include <map>
#include <vector>
using namespace std::chrono;
namespace Basic
{
    class Timers
    {
    public:
        static const int kPrecision = 10;//精度10MS
    public:
        static const int kLevelCount = 5;
        static const int kSlotsCount = 512;
    public:
        static Timers* getInstance()
        {
            static Timers t;
            return &t;
        }
    public:
        ~Timers();
        template<typename T>
        Timer* wait(microseconds lefttime, void(T::*onTimerEnd)(Timer*) = nullptr, T* object = nullptr);
        Timer* wait(microseconds lefttime, Timer::callback onTimerEnd = nullptr);

        template<typename T>
        Timer* repeat(microseconds interval, void(T::*onTimer)(Timer*), T* object, microseconds leftTime = microseconds(-1), void(T::*onTimerEnd)(Timer*) = nullptr);
        Timer* repeat(microseconds interval, Timer::callback onTimer, microseconds leftTime, Timer::callback  onTimerEnd);
        void tick();
        int64_t currentTicks() const;
        int64_t currentMicroseconds() const;
        void cancel(Timer* timer, bool raiseEvent);
        int64_t leftMicroseconds(const Timer* timer) const;
    private:
        Timers();
        int64_t calcDeadTicks(int64_t microseconds) const;
        void addToTail(std::list<Timer*>** head, Timer* var);
        int calcSlotIndex(int64_t microseconds);
        void cascade(int level);
        void raise();
    private:
        enum ProcessRet
        {
            None = 1 << 0,
            Remove = 1 << 1,
            Delete = 1 << 2 | Remove,
        };
        ProcessRet processTimer(Timer* timer, int currentSlot);
    private:
        std::list<Timer*>* timers_[kSlotsCount];
        int cursor_[kLevelCount];
        int64_t ticksSinceTimersStart_;
        int64_t startTime_;
    };

    template<typename T>
    Timer* Timers::wait(microseconds lefttime, void(T::*onTimerEnd)(Timer*) /*= nullptr*/, T* object /*= nullptr*/)
    {
        auto function = std::bind(onTimerEnd, object, std::placeholders::_1);
        return this->wait(lefttime, function);
    }

    template<typename T>
    Timer* Timers::repeat(microseconds interval, void(T::*onTimer)(Timer*), T* object, microseconds leftTime /*= microseconds(-1)*/, void(T::*onTimerEnd)(Timer*) /*= nullptr*/)
    {
        auto function1 = std::bind(onTimer, object, std::placeholders::_1);
        if (onTimerEnd == nullptr)
        {
            return this->repeat(interval, function1, leftTime, nullptr);
        }
        else
        {
            auto function2 = std::bind(onTimerEnd, object, std::placeholders::_1);
            return this->repeat(interval, function1, leftTime, function2);
        }
        return nullptr;
    }

    inline int64_t Timers::currentTicks() const
    {
        return ticksSinceTimersStart_;
    }

#ifdef WIN32
    #ifndef CAPI
        #ifdef _LIBRARY
            #define CAPI extern "C" __declspec(dllexport)
        #else
            #define CAPI extern "C" __declspec(dllimport)
        #endif
    #endif

    #ifndef stdcall
        #define stdcall _stdcall
    #endif
#endif

#ifdef WIN32

    ///此处的_stdcall必须有，否则会报错 The value of ESP was not properly
    typedef void(stdcall *TimerCallback)(Timer* timer);
    CAPI Timer* stdcall timer_wait(int64_t microseconds, TimerCallback onTimerEnd);
    CAPI int64_t stdcall timer_getLeftTime(Timer* timer);
    CAPI void stdcall timer_cancel(Timer* timer, bool raiseEvent);
    CAPI void stdcall timer_tick();
#elif __GNUC__
    typedef void(*TimerCallback)(Timer* timer);
    Timer*  timer_wait(int64_t microseconds, TimerCallback onTimerEnd);
    int64_t  timer_getLeftTime(Timer* timer);
    void  timer_cancel(Timer* timer, bool raiseEvent);
    void  timer_tick();
#endif
}

#endif // Timers_h__
