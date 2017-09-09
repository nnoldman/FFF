#ifndef CXBase_h__
#define CXBase_h__
//--------------------------------------------------------------------------------------------------
#include "base.h"
#include "Singleton.h"
#include "uString.h"
#include "Map.h"

#ifndef CPP1999
#include "HashMap.h"
#include "Pointer.h"
#include "WeakPointer.h"
#include "XMultiMap.h"
#endif

#include "Array.h"
#include "SArray.h"
#include "Stack.h"
#include "BiTree.h"
#include "RapidxmlLoader.h"
#include "RapidxmlWriter.h"
#include "FileName.hpp"
#include "XMath.h"
#include "Delegate.h"
#include "Buffer.h"
#include "CharBuffer.h"
#include "XIndex.h"
#include "uString.h"
#include "Random.h"
#include "Easer.h"
#include "TimeDim.h"
#include "Vector3.h"
#include "Color.h"
#include "ObjectPool.h"
#include "BitArray.h"
#include "IDObjects.h"
#include "Rect.h"
#include "Point2.h"
#include "Pointer.h"
#include "Lexer.h"

#include "Tree.h"
#include "uString.h"
#include "FilePathFinder.h"
#include "Platform.h"
#include "CommandLine.h"
#include "Value.h"
#include "Time_.h"
#include "StringHelper.h"
#include "Variable.h"

#define DeclareFilmObj(type)
#define DeclareFilmObjBase(type,parentType)
#define DeclareFilmTool
#define DeclareFilmToolGlobal

namespace Basic
{
/** @brief 查找一个数组或vector中cur之后的第一个符合条件的元素 **/
template<typename Array, typename T, typename CondtionObj>
T* dFindNextElementInArray(Array&  arr, T* cur, CondtionObj& funObj)
{
    bool existCur = false;
    for (auto& e : arr)
    {
        if (existCur && funObj(e))
        {
            return e;
        }
        if (e == cur)
        {
            existCur = true;
        }
    }
    return nullptr;
}
/** @brief
查找一棵树中(中序遍历)cur之后的第一个符合条件的元素
**/
template<typename T, typename CondtionObj>
T* dFindNextElementInTree(T*  parent, T* cur, CondtionObj& funObj)
{
    assert(parent);
    assert(cur);
    bool existCur = parent == cur;
    auto& children = parent->getChildren();
    for (auto& e : children)
    {
        if (existCur && funObj(e))
        {
            return e;
        }
        if (e == cur)
        {
            existCur = true;
        }
        T* tar = dFindNextElementInTree(e, cur, funObj);
        if (tar != nullptr)
            return tar;
    }
    return nullptr;
}
template<typename T, typename CondtionObj>
T* dFindNextElementInTreeCycle(T*  parent, T* cur, CondtionObj& funObj)
{
    Array<T*> dstArray;
    bool begin = parent == cur;
    bool end = parent == cur;
    takeElementToTopFromTreeToVector(dstArray, parent, cur, begin);
    takeElementToVectorUntil(dstArray, parent, cur, end);
    return dFindNextElementInArray(dstArray, cur, funObj);
}
template<typename T>
void takeElementToTopFromTreeToVector(Array<T*>& dstArray, T* parent, T* cur, bool& begin)
{
    if (parent == cur)
        begin = true;
    if (begin)
        dstArray.push_back(parent);
    auto& children = parent->getChildren();
    for (auto& a : children)
        takeElementToTopFromTreeToVector(dstArray, a, cur, begin);
}
template<typename T>
void takeElementToVectorUntil(Array<T*>& dstArray, T* parent, T* cur, bool& end)
{
    if (parent == cur)
    {
        end = true;
        return;
    }
    if (!end)
        dstArray.push_back(parent);
    auto& children = parent->getChildren();
    for (auto& a : children)
        takeElementToVectorUntil(dstArray, a, cur, end);

}

}



//--------------------------------------------------------------------------------------------------
#endif // CXBase_h__
