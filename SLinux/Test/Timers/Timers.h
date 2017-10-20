#ifndef Timers_h__
#define Timers_h__
#include <list>
#include <chrono>
#include "Timer.h"
#include <map>
#include <vector>
#include "ListNode.h"
using namespace std::chrono;

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
    Timer* repeat(microseconds interval, void(T::*onTimer)(Timer*) = nullptr, int  truns = -1, void(T::*onTimerEnd)(Timer*) = nullptr, T* object = nullptr);
    Timer* repeat(microseconds interval, Timer::callback onTimer = nullptr, int  truns = -1, Timer::callback  onTimerEnd = nullptr);
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
Timer* Timers::repeat(microseconds interval, void(T::*onTimer)(Timer*) /*= nullptr*/, int  truns  /*= -1*/, void(T::*onTimerEnd)(Timer*) /*= nullptr*/, T* object /*= nullptr*/)
{
    auto function1 = std::bind(onTimer, object, std::placeholders::_1);
    auto function2 = std::bind(onTimerEnd, object, std::placeholders::_1);
    return this->repeat(interval, function1, truns, function2);
}

inline int64_t Timers::currentTicks() const
{
    return ticksSinceTimersStart_;
}

#define API extern "C" __declspec(dllexport)

///此处的_stdcall必须有，否则会报错 The value of ESP was not properly
typedef  void(_stdcall *TimerCallback)(Timer* timer);
API Timer* _stdcall timer_wait(int64_t microseconds, TimerCallback onTimerEnd);
API int64_t _stdcall timer_getLeftTime(Timer* timer);
API void _stdcall timer_cancel(Timer* timer, bool raiseEvent);
API void _stdcall timer_tick();

#endif // Timers_h__
