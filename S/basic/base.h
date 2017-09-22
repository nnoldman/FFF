#ifndef base_h__
#define base_h__

#pragma region CommonType
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
#pragma endregion CommonType

#pragma region WindowsWarning
#pragma warning(disable:4244)
#pragma warning(disable:4251)//需要有 dll 接口由 class“GRectNode”的客户端使用
#pragma warning(disable:4275)
#pragma warning(disable:4305)
#pragma warning(disable:4800)
#pragma endregion WindowsWarning

#pragma region Params

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#define U_UNUSE(v) (void)v;

#pragma endregion Params

#pragma region Assert
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
#pragma endregion Assert

#pragma region STL
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#pragma endregion STL

#pragma region String
#include <string>
#include <xstring>
typedef std::string					stdString;
typedef std::vector<stdString>		stdStringArr;
//--------------------------------------------------------------------------------------------------
#define STRING_NO_RESULT stdString::npos
//--------------------------------------------------------------------------------------------------
#define QUOTE_NONE_STRING ""

typedef std::string StdString;
typedef std::wstring StdWString;

#ifdef UNICODE
typedef std::wstring CXString;
#else
typedef std::string CXString;
#endif


#define GCat(a,b)		a##b
#define GCatF(a,b)		GCat(a,b)
#define GCatCount(a)	GCatF(a,__COUNTER__)

#pragma endregion String

#pragma region Constant
#define WIDE_CHAR_FLAG 0X80
#define dIsWideChar(c) (WIDE_CHAR_FLAG & (c))

#define DOUBLE_MAX (1.79E+308)
#define DOUBLE_MIN (-DOUBLE_MAX)

#pragma endregion Constant

#pragma region Pragma
#ifdef _LIBRARY
#define COREAPI	__declspec(dllexport)
#else
#define COREAPI  __declspec(dllimport)
#endif

#ifdef _LIBRARY
#define API	extern "C" __declspec(dllexport)
#else
#define API  extern "C" __declspec(dllimport)
#endif

#define DefineOnce __declspec(selectany)
#pragma endregion Pragma

#pragma region Allocate

#define CXNew new
#define CXDelete delete

#define dSafeDelete(x) {if(x){ delete x;x=nullptr;}}
#define dSafeRelease(v) if(v){v->Release();v=nullptr;}

#define dMemberOffset(ClassName,memberName)\
	((int)&((ClassName*)0)->memberName)

#pragma endregion Allocate

#pragma region Math

#define dSequare(x) (x)*(x)
#define dIsSquareOf2(n) (0==(n&(n-1)))
#define dSumOfSequare(x,y) (dSequare(x)+dSequare(y))

#define dMin(x,y) ((x)<(y)?(x):(y))
#define dMax(x,y) ((x)>(y)?(x):(y))
#define dIsInRange(x,min,max) ( x>=min && x<=max )

#define dBIT(n) (1<<n)

#pragma endregion Math


inline void dDebugOutWithFile(const char* file, int line, const char* fmt, ...)
{
    //va_list arglist;
    //va_start ( arglist, fmt );
    //int nLen = XGetLength ( fmt, arglist ) /* + 1*/;
    //char* buffer = new char[nLen + 1];
    //XSPrintf ( buffer, nLen + 1, fmt, 0, arglist );
    //va_end ( arglist );
    //uString str, str2;
    //#ifdef WIN32
    //	str2.format( "%s(%d):", file, line );
    //	str.append ( str2 );
    //#endif
    //	str.append ( buffer );
    //	str.append ( "\n" );
#ifdef WIN32
    //OutputDebugStringA ( str.c_str() );
#else
    //std::cout << str.c_str();
#endif
    //delete[] buffer;
}

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
template<typename T>
void dSafeDeleteVector(T& v)
{
    if (v.size() > 0)
    {
        typename T::iterator it = v.begin();
        typename T::iterator end = v.end();
        for (; it != end; ++it)
        {
            dSafeDelete(*it);
        }
        v.clear();
    }
}
template<typename T, u32 N>
void dSafeDeleteArray(T * (&arr)[N])
{
    for (auto& i : arr)
        dSafeDelete(i);
}
template<typename T>
void dSafeDeleteMap2(T& v)
{
    typename T::iterator it = v.begin();
    typename T::iterator end = v.end();
    for (; it != end; ++it)
    {
        dSafeDelete(it->second);
    }
    v.clear();
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