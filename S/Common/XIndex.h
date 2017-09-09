#ifndef XIndex_h__
#define XIndex_h__

#pragma once
#include <string>
#include <stdio.h>
#pragma warning(push)
#pragma warning(disable:4996)
namespace Basic
{

class Index
{
    typedef unsigned int Type;
public:
    enum
    {
        InvalidIndex = ~0,
    };
    Index(void);
    Index(int i);
    ~Index(void);
protected:
    Type mValue;
public:
    bool IsValid() const
    {
        return mValue != InvalidIndex;
    }
    Type Value() const
    {
        return mValue;
    }
    void ToString(std::string& str)
    {
        char buffer[64] = { 0 };
        sprintf(buffer, "%d", mValue);
        str = buffer;
        //_itoa(mValue,(char*)str.c_str(),10);
    }
    Index& operator= (Type v)
    {
        mValue = v;
        return *this;
    }
    operator Type()
    {
        return mValue;
    }
    Index operator++ (int)
    {
        Index tmp = *this;
        ++mValue;
        return tmp;
    }
    Index& operator++()
    {
        ++mValue;
        return *this;
    }
    Index operator-- (int)
    {
        Index tmp = *this;
        --mValue;
        return tmp;
    }
    Index& operator--()
    {
        --mValue;
        return *this;
    }

    bool operator== (const Index& _Right) const
    {
        return mValue == _Right.mValue;
    }
};
inline bool operator < (const Index& lhs, const Index& rhs)
{
    return lhs.Value() < rhs.Value();
}
#pragma warning(pop)
inline Index::Index(int i)
    : mValue(i)
{

}
inline Index::Index(void)
{
}
inline Index::~Index(void)
{
}
}
#endif // XIndex_h__
