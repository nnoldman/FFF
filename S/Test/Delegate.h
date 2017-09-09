#pragma once
#include <vector>
#include <functional>
using namespace std;

template<typename RET = void>
class Delegate {
    typedef std::function<RET()> FunctionObjectType;
    class Functor {
      public:
        intptr_t functionPtr;
        intptr_t objectPtr;
        FunctionObjectType functionObject;
    };
  private:
    vector<Functor*> mFunctors;
  public:
    ~Delegate() {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            delete functor;
        }
        mFunctors.clear();
    }
  public:
    template<typename T>
    void add(RET(T::*func)(), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        Functor* functor = check(memberPtr, objPtr);
        assert(functor == nullptr);
        FunctionObjectType object = std::bind(func, obj);
        functor = new Functor();
        functor->functionPtr = memberPtr;
        functor->objectPtr = objPtr;
        functor->functionObject = object;
        mFunctors.push_back(functor);
    }

    template<typename T>
    void remove(RET(T::*func)(), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr) {
                mFunctors.erase(iter);
                break;
            }
        }
    }

    Functor* check(intptr_t memberPtr, intptr_t objPtr) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr)
                return functor;
        }
        return nullptr;
    }

    void invoke() {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            functor->functionObject();
        }
    }
};

template<typename RET = void, typename Arg1 = void>
class Delegate1 {
    typedef std::function<RET(Arg1)> FunctionObjectType;
    class Functor {
      public:
        intptr_t functionPtr;
        intptr_t objectPtr;
        FunctionObjectType functionObject;
    };
  private:
    vector<Functor*> mFunctors;
  public:
    ~Delegate1() {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            delete functor;
        }
        mFunctors.clear();
    }
  public:
    template<typename T>
    void add(RET(T::*func)(Arg1), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        Functor* functor = check(memberPtr, objPtr);
        assert(functor == nullptr);
        FunctionObjectType object = std::bind(func, obj, std::placeholders::_1);
        functor = new Functor();
        functor->functionPtr = memberPtr;
        functor->objectPtr = objPtr;
        functor->functionObject = object;
        mFunctors.push_back(functor);
    }

    template<typename T>
    void remove(RET(T::*func)(Arg1), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr) {
                mFunctors.erase(iter);
                break;
            }
        }
    }

    Functor* check(intptr_t memberPtr, intptr_t objPtr) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr)
                return functor;
        }
        return nullptr;
    }

    void invoke(Arg1 arg1) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            functor->functionObject(arg1);
        }
    }
};

template<typename RET = void, typename Arg1 = void, typename Arg2 = void>
class Delegate2 {
    typedef std::function<RET(Arg1, Arg2)> FunctionObjectType;
    class Functor {
      public:
        intptr_t functionPtr;
        intptr_t objectPtr;
        FunctionObjectType functionObject;
    };
  private:
    vector<Functor*> mFunctors;
  public:
    ~Delegate2() {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            delete functor;
        }
        mFunctors.clear();
    }
  public:
    template<typename T>
    void add(RET(T::*func)(Arg1, Arg2), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        Functor* functor = check(memberPtr, objPtr);
        assert(functor == nullptr);
        FunctionObjectType object = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2);
        functor = new Functor();
        functor->functionPtr = memberPtr;
        functor->objectPtr = objPtr;
        functor->functionObject = object;
        mFunctors.push_back(functor);
    }

    template<typename T>
    void remove(RET(T::*func)(Arg1, Arg2), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr) {
                mFunctors.erase(iter);
                break;
            }
        }
    }

    Functor* check(intptr_t memberPtr, intptr_t objPtr) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr)
                return functor;
        }
        return nullptr;
    }

    void invoke(Arg1 arg1, Arg1 arg2) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            functor->functionObject(arg1, arg2);
        }
    }
};

template<typename RET = void, typename Arg1 = void, typename Arg2 = void, typename Arg3 = void>
class Delegate3 {
    typedef std::function<RET(Arg1, Arg2, Arg3)> FunctionObjectType;
    class Functor {
      public:
        intptr_t functionPtr;
        intptr_t objectPtr;
        FunctionObjectType functionObject;
    };
  private:
    vector<Functor*> mFunctors;
  public:
    ~Delegate3() {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            delete functor;
        }
        mFunctors.clear();
    }
  public:
    template<typename T>
    void add(RET(T::*func)(Arg1, Arg2, Arg3), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        Functor* functor = check(memberPtr, objPtr);
        assert(functor == nullptr);
        FunctionObjectType object = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        functor = new Functor();
        functor->functionPtr = memberPtr;
        functor->objectPtr = objPtr;
        functor->functionObject = object;
        mFunctors.push_back(functor);
    }

    template<typename T>
    void remove(RET(T::*func)(Arg1, Arg2, Arg3), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr) {
                mFunctors.erase(iter);
                break;
            }
        }
    }

    Functor* check(intptr_t memberPtr, intptr_t objPtr) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr)
                return functor;
        }
        return nullptr;
    }

    void invoke(Arg1 arg1, Arg1 arg2, Arg3 arg3) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            functor->functionObject(arg1, arg2, arg3);
        }
    }
};

template<typename RET = void, typename Arg1 = void, typename Arg2 = void, typename Arg3 = void, typename Arg4 = void>
class Delegate4 {
    typedef std::function<RET(Arg1, Arg2, Arg3, Arg4)> FunctionObjectType;
    class Functor {
      public:
        intptr_t functionPtr;
        intptr_t objectPtr;
        FunctionObjectType functionObject;
    };
  private:
    vector<Functor*> mFunctors;
  public:
    ~Delegate4() {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            delete functor;
        }
        mFunctors.clear();
    }
  public:
    template<typename T>
    void add(RET(T::*func)(Arg1, Arg2, Arg3, Arg4), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        Functor* functor = check(memberPtr, objPtr);
        assert(functor == nullptr);
        FunctionObjectType object = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        functor = new Functor();
        functor->functionPtr = memberPtr;
        functor->objectPtr = objPtr;
        functor->functionObject = object;
        mFunctors.push_back(functor);
    }

    template<typename T>
    void remove(RET(T::*func)(Arg1, Arg2, Arg3, Arg4), T* obj) {
        intptr_t memberPtr = (intptr_t)(&func);
        intptr_t objPtr = (intptr_t)obj;
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            if (iter->functionPtr == memberPtr && iter->objectPtr == objPtr) {
                mCallbackObjects.erase(iter);
                break;
            }
        }
    }

    Functor* check(intptr_t memberPtr, intptr_t objPtr) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            if (functor->functionPtr == memberPtr && functor->objectPtr == objPtr)
                return functor;
        }
        return nullptr;
    }

    void invoke(Arg1 arg1, Arg1 arg2, Arg3 arg3, Arg4 arg4) {
        for (auto iter = mFunctors.begin(); iter != mFunctors.end(); ++iter) {
            auto functor = *iter;
            functor->functionObject(arg1, arg2, arg3, arg4);
        }
    }
};


