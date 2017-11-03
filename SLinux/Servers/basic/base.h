#ifndef base_h__
#define base_h__

///common type
typedef char Char;
typedef const char CChar;
typedef wchar_t WChar;
typedef const wchar_t CWChar;
typedef char s8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned char uchar;
typedef unsigned char byte;
typedef short s16;
typedef long long s64;
typedef float f32;

///params
#ifndef IN
    #define IN
#endif
#ifndef OUT
    #define OUT
#endif

#define U_UNUSE(v) (void)v;

///assert
#include <assert.h>
#if _DEBUG
    #define assert_false(exp)			assert(!(exp))
    #define assert_equal(a,b)			assert((a)==(b))
    #define CXASSERT(exp)				if(!(exp)){assert(0);}
    #define CXASSERT_RETURN(exp)		if(!(exp)){assert(0);return;}
    #define CXASSERT_RETURN_FALSE(exp)	if(!(exp)){assert(0);return false;}

    #define CXCheck(exp) assert(exp)

    #define CXASSERT_RESULT(exp)		if(FAILED(exp)){__debugbreak();return;}
    #define CXASSERT_RESULT_FALSE(exp)	if(FAILED((exp))) {__debugbreak();return false;}
#else
    #define assert_false(exp)			assert(!(exp))
    #define assert_equal(a,b)			assert((a)==(b))
    #define CXASSERT(exp)
    #define CXASSERT_RETURN(exp)		if(!(exp)){assert(0);return;}
    #define CXASSERT_RETURN_FALSE(exp)	if(!(exp)){assert(0);return false;}

    #define CXCheck(exp) assert(exp)

    #define CXASSERT_RESULT(exp)		if(FAILED(exp)){__debugbreak();return;}
    #define CXASSERT_RESULT_FALSE(exp)	if(FAILED((exp))) {__debugbreak();return false;}
#endif

///stl
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <list>
#include <string.h>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;
//--------------------------------------------------------------------------------------------------
#define QUOTE_NONE_STRING ""

#define GCat(a,b)		a##b
#define GCatF(a,b)		GCat(a,b)
#define GCatCount(a)	GCatF(a,__COUNTER__)

///project type
#ifdef WIN32
    #ifdef _LIBRARY
        #define COREAPI	__declspec(dllexport)
    #else
        #define COREAPI  __declspec(dllimport)
    #endif
#elif __GNUC__
    #ifdef _LIBRARY
        #define COREAPI
    #else
        #define COREAPI
    #endif
#endif


#ifdef _LIBRARY
    #define CAPI extern "C" __declspec(dllexport)
#else
    #define CAPI extern "C" __declspec(dllimport)
#endif



///platform
#ifdef WIN32
    #define declare_once __declspec(selectany)
    #define warning_push
    #define warning_pop
    #define warning_disable(c) #pragma warning(disable:c)
    #define stdcall _stdcall
#elif __GNUC__
    #define declare_once __attribute__((weakref))
    #define declare_var_once __attribute__((weak))

    #define warning_push #pragma GCC diagnostic push
    #define warning_pop #pragma GCC diagnostic pop
    #define warning_disable(c)
    #define stdcall
    //#define stdcall __attribute__((__stdcall__))
    //#define pack(n) __attribute__((aligned(n)))
    //#define pack_pop __attribute__((packed))
#endif

///memory
#define CXNew new
#define CXDelete delete

#define dSafeDelete(x) {if(x){ delete x;x=nullptr;}}
#define dSafeRelease(v) if(v){v->Release();v=nullptr;}

#define dMemberOffset(ClassName,memberName)\
    ((int)&((ClassName*)0)->memberName)

///math
#define dSequare(x) (x)*(x)
#define dIsSquareOf2(n) (0==(n&(n-1)))
#define dSumOfSequare(x,y) (dSequare(x)+dSequare(y))

#define dMin(x,y) ((x)<(y)?(x):(y))
#define dMax(x,y) ((x)>(y)?(x):(y))
#define dIsInRange(x,min,max) ( x>=min && x<=max )

#define dBIT(n) (1<<n)

#define dDebugOut(fmt,...) dDebugOutWithFile(__FILE__,__LINE__,fmt,__VA_ARGS__)

template<typename T>
void dConstruct(void* ptr)
{
    ::new (ptr) T;
}
template<typename T, typename E>
void dRemoveChild(T& v, E* e)
{
    typename T::iterator i = std::find(v.begin(), v.end(), e);
    if (i != v.end())
        v.erase(i);
}

#define dSafeDeleteVector(vec) \
    {\
        if (vec.size() > 0)\
        {\
            auto it = vec.begin();\
            auto end = vec.end();\
            for (; it != end; ++it)\
            {\
                dSafeDelete(*it);\
            }\
            vec.clear();\
        }\
    }

#define dSafeDeleteArray(arr) \
    {\
        for (auto& i : arr)\
            dSafeDelete(i);\
    }

#define dSafeDeleteMap2(v) \
    {\
        auto it = v.begin();\
        auto end = v.end();\
        for (; it != end; ++it)\
        {\
            dSafeDelete(it->second);\
        }\
        v.clear();\
    }

inline void dMemoryZero(void* p, size_t len)
{
    CXASSERT(p);
    memset(p, 0, len);
}
#define dMemoryZeroStruct(p) memset(p,0,sizeof(*p))
#define dToggle(b) (b=!b)

inline void dMemoryCopy(void* dst, void* src, size_t len)
{
    CXASSERT(dst && src);
    memcpy(dst, src, len);
}
template<typename T, u32 N>
void dMemoryZeroArray(T(&arr)[N])
{
    dMemoryZero(&arr, sizeof(T) *N);
}
inline bool dStrEqual(const char* s1, const char* s2)
{
    return 0 == strcmp(s1, s2);
}
inline size_t dStrLen(const wchar_t* s)
{
    CXASSERT(s != 0);
    return wcslen(s);
}
inline size_t dStrLen(const char* s)
{
    CXASSERT(s != 0);
    return strlen(s);
}

template<typename T, s32 N>
const s32 dArrayCount(T(&arr)[N])
{
    return N;
}

template<typename T1, typename T2>
void dCast(T1& dst, T2* src)
{
    dst = *((T1*)src);
}
template<typename T1, typename T2>
void dCast(T1* dst, T2 src)
{
    *((T2*)dst) = src;
}

#endif // base_h__