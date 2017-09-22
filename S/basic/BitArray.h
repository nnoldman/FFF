#pragma once
#include "base.h"
namespace Basic
{
typedef int IndexType;
typedef unsigned char BYTE;
template<IndexType BYTE_COUNT>
class BitArray
{
public:
    enum
    {
        BYTE_SIZE = 8,
        THIS_SIZE = BYTE_COUNT,
        BIT_SIZE = BYTE_COUNT * BYTE_SIZE,
    };
    BitArray()
    {
        dMemoryZeroArray(mBytes);
    }

    template<typename T>
    void fillFrom(T* val)
    {
        dMemoryCopy(mBytes, val, THIS_SIZE);
    }

    template<typename T>
    void fillTo(T* val)
    {
        dMemoryCopy(val, mBytes, THIS_SIZE);
    }

    void setAll(bool b)
    {
        for (IndexType i = 0; i < BYTE_COUNT; ++i)
            mBytes[i] = b ? 0XFF : 0;
    }

    void bitClear(IndexType idx)
    {
        CXASSERT_RETURN(idx < BIT_SIZE);

        IndexType col = idx % BYTE_SIZE;
        IndexType row = idx / BYTE_SIZE;

        mBytes[row] &= (~(1 << col));
    }
    void setBit(IndexType i, bool b)
    {
        if (b)
            bitSet(i);
        else
            bitClear(i);
    }
    void bitSet(IndexType idx)
    {
        CXASSERT_RETURN(idx < BIT_SIZE);

        IndexType col = idx % BYTE_SIZE;
        IndexType row = idx / BYTE_SIZE;

        mBytes[row] |= (1 << col);
    }

    bool get(IndexType idx) const
    {
        CXASSERT_RETURN_FALSE(idx < BIT_SIZE);

        IndexType col = idx % BYTE_SIZE;
        IndexType row = idx / BYTE_SIZE;
        return (1 << col) == (mBytes[row] & (1 << col));
    }

    bool operator[](IndexType idx) const
    {
        return get(idx);
    }
    IndexType count(bool val) const
    {
        IndexType cnt = 0;
        for (int i = 0; i < BIT_SIZE; ++i)
        {
            if (val == get(i))
                cnt++;
        }
        return cnt;
    }
protected:
    BYTE mBytes[BYTE_COUNT];
};
typedef BitArray<4> BitArray32;
typedef BitArray<2> BitArray16;
typedef BitArray<1> BitArray8;
}