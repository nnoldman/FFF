#ifndef XRandom_h__
#define XRandom_h__
#include <stdlib.h>
#include <time.h>
#include <assert.h>
//-------------------------------------------------------------------------
/**
@brief 生成随机数
@author nnboy,28/7/2014  22:30
*/
class CXRandomIniter
{
public:
    CXRandomIniter();
};

class Random
{
    friend class CXRandomIniter;
public:
    /** 生成指定范围的整数随机数 **/
    inline int randI(int minv, int maxv)
    {
        assert(minv < maxv);
        return minv + randI() % (maxv - minv + 1);
    }
    inline int randI()
    {
        return rand();
    }
    inline float randF()
    {
        return (float) randI() / RAND_MAX;
    }
    inline float randF(float minv, float maxv)
    {
        assert(minv < maxv);
        return (maxv - minv) * randF() + minv;
    }
private:
    static void init()
    {
        srand((unsigned int) time(0));
    }
    static CXRandomIniter mRandomIniter;
};
DefineOnce Random gRandom;
inline CXRandomIniter::CXRandomIniter()
{
    Random::init();
}

DefineOnce CXRandomIniter Random::mRandomIniter;
#endif // XRandom_h__
