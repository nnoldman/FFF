#include "base.h"
#include "Singleton.h"

#ifndef CPP1999
    #include "Pointer.h"
    #include "WeakPointer.h"
#endif

#include "Array.h"
#include "Stack.h"
#include "BiTree.h"
#include "RapidxmlLoader.h"
#include "RapidxmlWriter.h"
#include "Delegate.h"
#include "Buffer.h"
#include "CharBuffer.h"
#include "Timer.h"
#include "Timers.h"

#include "Random.h"
#include "Easer.h"
#include "Color.h"
#include "ObjectPool.h"
#include "BitArray.h"
#include "IDGenerator.h"
#include "Point2.h"
#include "Pointer.h"
#include "Lexer.h"
#include "Math.h"

#include "Tree.h"

#include "Platform.h"
#include "CommandLine.h"
#include "Time_.h"
#include "StringHelper.h"
#include "Variable.h"
#include "AnyValue.h"
#include "FileLoader.h"
#include "ServerID.h"
#include "Platform.h"

namespace Basic {
    /** @brief 查找一个数组或vector中cur之后的第一个符合条件的元素 **/
    template<typename Array, typename T, typename CondtionObj>
    T* dFindNextElementInArray(Array&  arr, T* cur, CondtionObj& funObj) {
        bool existCur = false;
        for (auto& e : arr) {
            if (existCur && funObj(e)) {
                return e;
            }
            if (e == cur) {
                existCur = true;
            }
        }
        return nullptr;
    }
    /** @brief
    查找一棵树中(中序遍历)cur之后的第一个符合条件的元素
    **/
    template<typename T, typename CondtionObj>
    T* dFindNextElementInTree(T*  parent, T* cur, CondtionObj& funObj) {
        assert(parent);
        assert(cur);
        bool existCur = parent == cur;
        auto& children = parent->getChildren();
        for (auto& e : children) {
            if (existCur && funObj(e)) {
                return e;
            }
            if (e == cur) {
                existCur = true;
            }
            T* tar = dFindNextElementInTree(e, cur, funObj);
            if (tar != nullptr)
                return tar;
        }
        return nullptr;
    }
    template<typename T, typename CondtionObj>
    T* dFindNextElementInTreeCycle(T*  parent, T* cur, CondtionObj& funObj) {
        Array<T*> dstArray;
        bool begin = parent == cur;
        bool end = parent == cur;
        takeElementToTopFromTreeToVector(dstArray, parent, cur, begin);
        takeElementToVectorUntil(dstArray, parent, cur, end);
        return dFindNextElementInArray(dstArray, cur, funObj);
    }
    template<typename T>
    void takeElementToTopFromTreeToVector(Array<T*>& dstArray, T* parent, T* cur, bool& begin) {
        if (parent == cur)
            begin = true;
        if (begin)
            dstArray.push_back(parent);
        auto& children = parent->getChildren();
        for (auto& a : children)
            takeElementToTopFromTreeToVector(dstArray, a, cur, begin);
    }
    template<typename T>
    void takeElementToVectorUntil(Array<T*>& dstArray, T* parent, T* cur, bool& end) {
        if (parent == cur) {
            end = true;
            return;
        }
        if (!end)
            dstArray.push_back(parent);
        auto& children = parent->getChildren();
        for (auto& a : children)
            takeElementToVectorUntil(dstArray, a, cur, end);
    }

    inline void split(const std::string& s, const std::string& c, std::vector<std::string>& ret) {
        ret.clear();
        std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;
        while (std::string::npos != pos2) {
            ret.push_back(s.substr(pos1, pos2 - pos1));
            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if (pos1 != s.length())
            ret.push_back(s.substr(pos1));
    }
    inline void split(const char* s, const std::string& c, std::vector<std::string>& ret) {
        std::string str;
        str = s;
        split(str, c, ret);
    }

    template<typename Map>
    bool getValue(Map& map, typename Map::key_type key, typename Map::mapped_type& value) {
        auto it = map.find(key);
        if (it == map.end())
            return false;
        value = it->second;
        return true;
    }
}


