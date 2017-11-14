#ifndef Random_h__
#define Random_h__
#include <stdlib.h>
#include <time.h>
#include <assert.h>
//-------------------------------------------------------------------------
/**
@brief ���������
@author nnboy,28/7/2014  22:30
*/
namespace Basic
{
    class Random
    {
    private:
        Random()
        {
            srand((unsigned int)time(0));
        }
    public:

        /** ����ָ����Χ�����������,[minv,maxv] **/
        inline int randI(int minv, int maxv)
        {
            assert(minv < maxv);
            unsigned int num = (unsigned int)((randI() << 16) + randI());
            return minv + num % (maxv - minv + 1);
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
    public:
        static Random& getInstance()
        {
            static Random random;
            return random;
        }
    };
}
#endif // Random_h__
