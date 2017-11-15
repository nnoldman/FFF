#ifndef Timer_h__
#define Timer_h__
#include <functional>
#include <chrono>
using namespace std::chrono;
namespace Basic {
    class Timer {
      public:
        typedef std::function<void(Timer*)> callback;
      public:
        ~Timer();
        void cancel(bool raise = false);
        int64_t nextHitTicks() const;
        int64_t intervalMillseconds() const;
        int64_t leftMillseconds() const;
        int leftSeconds() const;
        std::chrono::milliseconds life() const;
      private:
        Timer();
        callback onTimer_;
        callback onEnd_;
        int64_t lifeMillseconds_;
        int64_t intervalMillseconds_;
        int64_t nextHitTicks_;
        int64_t leftTruns_;
        int position_;
        friend class Timers;
    };
    inline int64_t Timer::nextHitTicks() const {
        return this->position_;
    }
    inline int64_t Timer::intervalMillseconds() const {
        return this->intervalMillseconds_;
    }
}


#endif // Timer_h__
