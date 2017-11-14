#pragma once
#include <stdint.h>
class Reference {
  public:
    Reference(void)
        : mRefCount(nullptr)
        , mData(nullptr)
        , mSize(0) {
        addref();
    }
    ~Reference(void) {
        decref();

        mSize = 0;
    }
    size_t addref() {
        if (mRefCount == nullptr)
            mRefCount = new int(0);
        assert(*mRefCount < INT32_MAX/*std::numeric_limits<int>::max()*/);
        ++(*mRefCount);
        return *mRefCount;
    }
    size_t decref() {
        if (mRefCount == nullptr)
            return 0;
        assert(*mRefCount > 0);
        --(*mRefCount);
        if (*mRefCount == 0) {
            if (mData != nullptr) {
                delete mData;
                mData = nullptr;
            }
            if (mRefCount != nullptr) {
                delete mRefCount;
                mRefCount = nullptr;
            }
        }
        if (mRefCount)
            return *mRefCount;
        return 0;
    }
    Reference(const Reference& src)
        : mRefCount(nullptr)
        , mData(nullptr)
        , mSize(0) {
        copy(src);
    }
    Reference& operator= (const Reference& src) {
        copy(src);
        return *this;
    }
    inline char* pointer() const {
        return mData;
    }
    inline wchar_t* pointerw() const {
        return mWData;
    }
    inline void clear() {
        delete[]mData;
        mData = nullptr;
    }
    inline size_t capcity() const {
        return mSize;
    }
    void copyData(const Reference& counter) {
        if (counter.capcity() > 0) {
            reallocInner(counter.capcity());
            assert(mSize == counter.capcity());
            dMemoryCopy(mData, counter.pointer(), mSize);
        }
    }
    void reallocate(size_t size) {
        size += 1;
        reallocInner(size);
    }
    inline void setzero() {
        if (mData)
            dMemoryZero(mData, mSize);
    }
  private:
    void reallocInner(size_t size) {
        setzero();
        if (size == mSize)
            return;
        if (size > mSize) {
            /** @brief extend capacity **/
            expand(size);
            return;
        }
        /** @brief shrink capacity **/
        size_t tarcnt = mSize;
        while (size < tarcnt && tarcnt > 1) {
            tarcnt = tarcnt >> 1;
        }
        if (tarcnt != 0X10000000)
            tarcnt = tarcnt << 1;
        else
            tarcnt = size;
        if (tarcnt == mSize)
            return;
        mSize = tarcnt;
        realloc();
    }
    void copy(const  Reference& src) {
        decref();
        assert(src.mRefCount != nullptr);
        mRefCount = src.mRefCount;
        mData = src.pointer();
        mSize = src.capcity();
        addref();
    }
    inline void  expand(size_t size) {
        assert(size);
        size_t tarcnt = 0X10000000;
        while (0 == (tarcnt & size)) {
            tarcnt = tarcnt >> 1;
        }
        if (tarcnt != size) {
            if (tarcnt != 0X10000000)
                tarcnt = tarcnt << 1;
            else
                tarcnt = size;
        }
        mSize = tarcnt;
        realloc();
    }
    void realloc() {
        delete[]mData;
        mData = new char[mSize];
        setzero();
    }

  private:
    union {
            char* mData;
            wchar_t* mWData;
        };
    size_t mSize;
    int* mRefCount;
};

