#ifndef TimeDim_h__
#define TimeDim_h__

namespace Basic
{
template<u64 N>
class TimeDim
{
public:
    static const u64 DIM = N;

    TimeDim(void)
    {
        value_ = 0;
    }

    TimeDim(u64 v)
    {
        value_ = v;
    }

    template<u64 N2>
    TimeDim(TimeDim<N2>& rhs)
    {
        value_ = rhs.DIM * rhs.mValue / DIM;
    }

    operator u64()
    {
        return value_;
    }

    template<u64 N2>
    bool operator== (TimeDim<N2>& rhs)
    {
        return getMillSeconds() == rhs.getMillSeconds();
    }

    template<u64 N2>
    bool operator<= (const TimeDim<N2>& rhs)
    {
        return getMillSeconds() <= rhs.getMillSeconds();
    }

    inline u64 getSeconds() const
    {
        return DIM * 0.001 * value_;
    }
    inline u64 getMillSeconds() const
    {
        return DIM * value_;
    }
protected:
	u64 value_;
};



typedef TimeDim<1> MillSeconds;
typedef TimeDim<1000> Seconds;
typedef TimeDim<1000 * 60> Minutes;
typedef TimeDim<1000 * 60 * 60> Hours;
typedef TimeDim<1000 * 60 * 60 * 24> Days;
}

#endif // TimeDim_h__
