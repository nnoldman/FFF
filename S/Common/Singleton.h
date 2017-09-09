#ifndef XSingleton_h__
#define XSingleton_h__

namespace Basic
{
template<typename T>
class Singleton
{
public:
    typedef Singleton<T> MyType;
private:
    Singleton()
    {
    }
    Singleton(const Singleton&);
    Singleton& operator= (const Singleton&);
public:
    virtual ~Singleton()
    {
    }
    static T*& getInstance()
    {
        static T* sInstance_ = nullptr;
        if (!sInstance_)
        {
            sInstance_ = new T;
        }
        return sInstance_;
    }
    static  T& getSingleton()
    {
        return *getInstance();
    }
    static void destoryInstance()
    {
        T*& p = getInstance();
        dSafeDelete(p);
    }
    static T* sInstance_;
};

template<typename T>
__declspec(selectany)
T* Singleton<T>::sInstance_ = nullptr;
}

#endif // XSingleton_h__
