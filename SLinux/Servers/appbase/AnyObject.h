#ifndef AnyObject_h__
#define AnyObject_h__
#include "Poco/Any.h"
using namespace Poco;
class AnyObject
{
public:
    AnyObject();
    AnyObject(AnyObject& other);
    AnyObject(const AnyObject& other);
    AnyObject(Any object);
    AnyObject(const char* value);
    AnyObject& operator=(Any object);
    AnyObject& operator=(AnyObject& other);
    ~AnyObject();

    template<typename T>
    T* get();
    template<typename T>
    AnyObject(T value);

    string toString();
public:
    bool isString() const;
private:
    Any* object_;
};

template<typename T>
inline T * AnyObject::get()
{
    return Poco::AnyCast<T>(object_);
}

template<typename T>
AnyObject::AnyObject(T value)
{
    this->object_ = new Any(value);
}
#endif // AnyObject_h__
