#ifndef Timers_h__
#define Timers_h__
#include <list>
#include <chrono>
#include "Timer.h"
#include <map>
#include <vector>
#include <memory>
using namespace std;
using namespace std::chrono;
namespace Basic {
    typedef shared_ptr<Basic::Timer> TimerPtr;
    class Timers {
      public:
        static const int kPrecision = 10;//精度10MS
      public:
        static const int kLevelCount = 5;
        static const int kSlotsCount = 512;
      public:
        static Timers* getInstance() {
            static Timers t;
            return &t;
        }
      public:
        ~Timers();
        template<typename T>
        TimerPtr wait(int64_t lefttimeMillSeconds, void(T::*onTimerEnd)(Timer*) = nullptr, T* object = nullptr);
        TimerPtr wait(int64_t lefttimeMillSeconds, Timer::callback onTimerEnd = nullptr);

        template<typename T>
        TimerPtr repeat(int64_t intervalMillSeconds, void(T::*onTimer)(Timer*), T* object, int64_t leftTime = -1, void(T::*onTimerEnd)(Timer*) = nullptr);
        TimerPtr repeat(int64_t intervalMillSeconds, Timer::callback onTimer, int64_t leftTime, Timer::callback  onTimerEnd);
        void tick();
        int64_t currentTicks() const;
        int64_t currentMillseconds() const;
        void cancel(Timer* timer, bool raiseEvent);
        int64_t leftMicroseconds(const Timer* timer) const;
      private:
        Timers();
        int64_t calcDeadTicks(int64_t microseconds) const;
        void addToTail(std::list<TimerPtr>** head, TimerPtr var);
        int calcSlotIndex(int64_t microseconds);
        void cascade(int level);
        void raise();
      private:
        enum ProcessRet {
            None = 1 << 0,
            Remove = 1 << 1,
            Delete = 1 << 2 | Remove,
        };
        ProcessRet processTimer(TimerPtr timer, int currentSlot);
      private:
        std::list<TimerPtr>* timers_[kSlotsCount];
        int cursor_[kLevelCount];
        int64_t ticksSinceTimersStart_;
        int64_t startTime_;
    };

    template<typename T>
    TimerPtr Timers::wait(int64_t lefttimeMillSeconds, void(T::*onTimerEnd)(Timer*) /*= nullptr*/, T* object /*= nullptr*/) {
        auto function = std::bind(onTimerEnd, object, std::placeholders::_1);
        return this->wait(lefttimeMillSeconds, function);
    }

    template<typename T>
    TimerPtr Timers::repeat(int64_t intervalMillSeconds, void(T::*onTimer)(Timer*), T* object, int64_t leftTimeMillSeconds /*= microseconds(-1)*/, void(T::*onTimerEnd)(Timer*) /*= nullptr*/) {
        auto function1 = std::bind(onTimer, object, std::placeholders::_1);
        if (onTimerEnd == nullptr) {
            return this->repeat(intervalMillSeconds, function1, leftTimeMillSeconds, nullptr);
        } else {
            auto function2 = std::bind(onTimerEnd, object, std::placeholders::_1);
            return this->repeat(intervalMillSeconds, function1, leftTimeMillSeconds, function2);
        }
        return nullptr;
    }

    inline int64_t Timers::currentTicks() const {
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
