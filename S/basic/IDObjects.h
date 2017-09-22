#pragma once
#include "HashMap.h"
namespace Basic {
template<typename T>
class IDObjects {
  public:
    IDObjects(void);
    ~IDObjects();
    /** @brief
    @return objID
    **/
    u32 addObj(T* obj);
    void removeObj(u32 id);
    void destoryObj(u32 id);
    T* getObj(u32 id);
  protected:
    u32 mObjCount;
    HashMap<u32, T*> mObjMap;
};

template<typename T>
IDObjects<T>::~IDObjects() {
    mObjCount = 0;
    mObjMap.clear();
}

template<typename T>
IDObjects<T>::IDObjects(void) {
    mObjCount = 0;
}

template<typename T>
T* IDObjects<T>::getObj(u32 id) {
    T* obj = nullptr;
    mObjMap.Get(id, obj);
    return obj;
}

template<typename T>
void IDObjects<T>::destoryObj(u32 id) {
    auto pair = mObjMap.find(id);
    if (pair != mObjMap.end()) {
        dSafeDelete(pair->second);
        mObjMap.erase(pair);
    }
}

template<typename T>
void IDObjects<T>::removeObj(u32 id) {
    mObjMap.erase(id);
}

template<typename T>
u32 IDObjects<T>::addObj(T* obj) {
    mObjCount++;
    mObjMap.Insert(mObjCount, obj);
    return mObjCount;
}
}

