#include "stdafx.h"
#include "test_delegate.h"
#include "Delegate.h"
class ObjectA
{
public:
    Delegate<void> onOpenUI;
    Delegate1<void, int> onOpenUI1;
    Delegate2<void, int, int> onOpenUI2;
    Delegate3<void, int, int, int> onOpenUI3;
    int name = 12;
public:
    void OpenUI()
    {
        onOpenUI.invoke();
    }
};

inline bool operator== (const ObjectA& lhs, const ObjectA& rhs)
{
    return lhs.name == rhs.name;
}


class VoidIntDelegate
{
private:
    vector<std::function<void(int)>> mCallbackObjects;
public:
    template<typename FX, typename T>
    void add(FX&& func, T* obj)
    {
        std::function<void(int)> object = std::bind(func, obj, std::placeholders::_1);
        //for (auto iter = mCallbackObjects.begin(); iter != mCallbackObjects.end(); ++iter) {
        //    if (std::equal_to(*iter, object)) {
        //    }
        //}

        //assert(std::find(mCallbackObjects.begin(), mCallbackObjects.end(), object) == mCallbackObjects.end());
        mCallbackObjects.push_back(object);
    }

    void invoke(int num)
    {
        for (auto iter = mCallbackObjects.begin(); iter != mCallbackObjects.end(); ++iter)
        {
            (*iter)(num);
        }
    }
};


test_delegate::test_delegate()
{
    //base1.onOpenUI.add(this, &test_delegate::onOpenUI);

    {
        //std::function<void(int)> voidIntObjects = std::bind(&test_delegate::onOpenUI, this, std::placeholders::_1);

        //VoidIntDelegate delegates;
        //delegates.add(&test_delegate::onOpenUI, this);
        //delegates.invoke(5);
    }
    {
        ObjectA objA;
        objA.onOpenUI.add(&test_delegate::onOpenUI, this);
        objA.onOpenUI1.add(&test_delegate::onOpenUI, this);
        objA.onOpenUI2.add(&test_delegate::onOpenUI, this);
        objA.onOpenUI3.add(&test_delegate::onOpenUI, this);

        objA.onOpenUI.invoke();
        objA.onOpenUI1.invoke(5);
        objA.onOpenUI2.invoke(5, 6);
        objA.onOpenUI3.invoke(5, 7, 8);

        objA.onOpenUI.remove(&test_delegate::onOpenUI, this);
        objA.onOpenUI1.remove(&test_delegate::onOpenUI, this);
        objA.onOpenUI2.remove(&test_delegate::onOpenUI, this);
        objA.onOpenUI3.remove(&test_delegate::onOpenUI, this);
    }

    {
        //ObjectA base1;
        //vector<ObjectA> basearray;
        //basearray.push_back(base1);
        //assert(basearray.end() != std::find(basearray.begin(), basearray.end(), base1));
    }
}

test_delegate::~test_delegate()
{
}
