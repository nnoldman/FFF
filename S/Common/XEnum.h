#pragma once
#include "Array.h"
struct uEnumStruct
{
    const char* mName;
    const int mValue;
    uEnumStruct(int var, const char* name)
        : mName(name), mValue(var)
    {
    }
};

typedef Array<uEnumStruct*> uEnumStructList;
template<typename T>
class uEnumStructHelper
{
protected:
    static uEnumStructList* mStructList;
    static void regist();
public:
    static uEnumStructList& getStructList();

    ~uEnumStructHelper();
    uEnumStructHelper();
};

template<typename T>
uEnumStructHelper<T>::uEnumStructHelper()
{
    if (getStructList().empty())
        regist();
}

template<typename T>
uEnumStructHelper<T>::~uEnumStructHelper()
{
    dSafeDeleteVector(*mStructList);
    dSafeDelete(mStructList);
}

template<typename T>
uEnumStructList& uEnumStructHelper<T>::getStructList()
{
    if (mStructList == nullptr)
    {
        mStructList = new uEnumStructList;
    }
    return *mStructList;
}
template<typename T>
DefineOnce uEnumStructList* uEnumStructHelper<T>::mStructList = nullptr;

