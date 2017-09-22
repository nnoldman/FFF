#pragma once
//template<typename T>
//class WeakPointer : public std::weak_ptr<T>
//{
//public:
//    typedef WeakPointer<T> MyType;
//    typedef std::weak_ptr<T> Super;
//    MyType& operator=(Pointer<T> rhs)
//    {
//    }
//    T* operator->()
//    {
//        assert(this->expired());
//        return this->lock();
//    }
//    operator bool()
//    {
//        return this->expired() && this->lock() != nullptr;
//    }
//};

