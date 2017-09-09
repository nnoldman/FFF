#ifndef Buffer_h__
#define Buffer_h__

//-------------------------------------------------------------------------
/**
	@brief
	@author nnboy,29/9/2014  12:08
*/
namespace Basic
{
class Buffer
{
public:
    Buffer();
    ~Buffer();
    Buffer(size_t byteCnt);
    void reAllocate(size_t byteSize);
    void reallocateByElementCount(size_t cnt);
    void clear();
    inline void setElementByteCount(size_t size);
    inline size_t length();
    inline size_t size();
    inline void setSize(size_t size);
    inline size_t capacity() const;
    inline char* getBuffer() const;
    inline char* currentPointer() const;
    inline wchar_t* getWChar();
    inline const char* c_str() const;
    inline void copyTo(void* dst);
    inline void copyFrom(void* src);
    inline void setChar(size_t idx, char c);
    template<typename T>
    void addElement(T v);
    template<typename T>
    void addElement(T* v, size_t cnt);
    void addString(const char* str);
    void setString(const char* str);

    size_t readInt(int& var);
    size_t write(int& var);
    size_t write(u32& var);
    size_t getPosition();
    size_t forwardPosition(int tranlate);

    Buffer& operator=(const char* str);

    template<typename T>
    inline void set(size_t idx, const T& v)
    {
        *((T*)&mData[idx * sizeof(T)]) = v;
    }

    template<typename T>
    inline T& get(size_t idx)
    {
        return* ((T*) &mData[idx * sizeof(T)]) ;
    }

    inline void zero()
    {
        dMemoryZero(mData, length());
    }
protected:
    inline void free()
    {
        if (mData != nullptr)
        {
            delete[] mData;
            mData = nullptr;
        }
    }
protected:
    size_t mPosition;
    size_t mElementByteCount;
    size_t mCapacity;
    size_t mCount;
    union
    {
        char* mData;
        wchar_t* mWData;
    };
};
inline size_t Buffer::length()
{
    return mCapacity * mElementByteCount;
}
inline char* Buffer::getBuffer() const
{
    return mData;
}

inline char* Buffer::currentPointer() const
{
    return (char*)(mData + mPosition);
}

inline const char* Buffer::c_str() const
{
    return (const char*) mData;
}
inline void Buffer::setElementByteCount(size_t size)
{
    mElementByteCount = size;
}

inline void Buffer::copyTo(void* dst)
{
    dMemoryCopy(dst, mData, mCount * mElementByteCount);
}

inline void Buffer::copyFrom(void* src)
{
    dMemoryCopy(mData, src, mCapacity * mElementByteCount);
}
template<typename T>
inline void Buffer::addElement(T* v, size_t cnt)
{
    dMemoryCopy(&mData[mCount * mElementByteCount], v, cnt * mElementByteCount);
    mCount += cnt;
}

template<typename T>
inline void Buffer::addElement(T v)
{
    * ((T*) &mData[mCount * sizeof(T)]) = v;
    mCount++;
}


inline size_t Buffer::size()
{
    return mCount;
}

inline void Buffer::setChar(size_t idx, char c)
{
    assert(mData);
    mData[idx] = c;
}
inline size_t Buffer::capacity() const
{
    return mCapacity;
}

inline void Buffer::clear()
{
    mCount = 0;
    dMemoryZero(mData, length());
    mPosition = 0;
}
inline Buffer::Buffer(void)
{
    mData = 0;
    mCount = 0;
    mCapacity = 0;
    mElementByteCount = 1;
}
inline Buffer::Buffer(size_t byteCnt)
{
    mData = 0;
    mCount = 0;
    mCapacity = byteCnt;
    mElementByteCount = 1;
    reAllocate(mCapacity);
}


inline Buffer::~Buffer(void)
{
    this->free();
}

inline void Buffer::reAllocate(size_t byteSize)
{
    this->free();
    mData = new char[byteSize];
    if (mElementByteCount > 0)
        mCapacity = byteSize / mElementByteCount;
    dMemoryZero(mData, byteSize);
}

inline void Buffer::reallocateByElementCount(size_t cnt)
{
    this->free();
    mCapacity = cnt;
    mData = new char[mCapacity * mElementByteCount];
    dMemoryZero(mData, mCapacity * mElementByteCount);
}

inline void Buffer::setSize(size_t size)
{
    mCount = size;
}

inline wchar_t* Buffer::getWChar()
{
    return mWData;
}

inline void Buffer::addString(const char* str)
{
    assert(str);
    assert(mData);
    assert(mElementByteCount == 1);
    size_t cnt = strlen(str) + 1;
    assert(cnt <= capacity());
    dMemoryCopy(&mData[mCount * mElementByteCount], (void*)str, cnt * mElementByteCount);
    mCount += cnt;
}

inline void Buffer::setString(const char* str)
{
    this->clear();
    addString(str);
}

inline size_t Buffer::readInt(int& var)
{
    var = (*(int*)(mData + mPosition));
    mPosition += 4;
    return mPosition;
}

inline size_t Buffer::write(int& var)
{
    (*(int*)(mData + mPosition)) = var;
    mPosition += sizeof(int);
    return mPosition;
}

inline size_t Buffer::write(u32& var)
{
    (*(u32*)(mData + mPosition)) = var;
    mPosition += sizeof(u32);
    return mPosition;
}

inline size_t Buffer::getPosition()
{
    return mPosition;
}

inline size_t Buffer::forwardPosition(int tranlate)
{
    mPosition += tranlate;
    return mPosition;
}

inline Buffer& Buffer::operator=(const char* str)
{
    this->clear();
    addString(str);
    return *this;
}

}
#endif // Buffer_h__
