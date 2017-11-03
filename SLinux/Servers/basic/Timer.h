#ifndef Timer_h__
#define Timer_h__
#include <functional>
#include <chrono>
using namespace std::chrono;
namespace Basic
{
    class Timer
    {
    public:
        typedef std::function<void(Timer*)> callback;
    public:
        ~Timer();
        void cancel(bool raise = false);
        int64_t nextHitTicks() const;
        int64_t intervalMicroseconds() const;
        int64_t leftMicroseconds() const;
        int leftSeconds() const;
        std::chrono::microseconds life() const;
    private:
        Timer();
        std::function<void(Timer*)> onTimer_;
        std::function<void(Timer*)> onEnd_;
        std::chrono::microseconds life_;
        std::chrono::microseconds interval_;
        int64_t nextHitTicks_;
        int64_t leftTruns_;
        int position_;
        friend class Timers;
    };
    inline int64_t Timer::nextHitTicks() const
    {
        return this->position_;
    }
    inline int64_t Timer::intervalMicroseconds() const
    {
        return this->interval_.count();
    }
}


#endif // Timer_h__
