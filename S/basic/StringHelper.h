#ifndef StringHelper_h__
#define StringHelper_h__
#include <xstring>
#include "Buffer.h"
#include "CharBuffer.h"
#include "uString.h"
namespace Basic
{
namespace StringHelper
{
template<typename T>
void toString(std::string& dst, T* var)
{
    dst = to_string(*var);
}
void toString(std::string& dst, uString* var);
void toString(std::string& dst, string* var);
void toString(std::string& dst, bool* var);


void setValue(const char* val, string* var);
void setValue(const char* val, uString* var);
void setValue(const char* val, int* var);
void setValue(const char* val, float* var);
void setValue(const char* val, bool* var);
void setValue(const char* val, unsigned int* var);
void setValue(const char* val, long* var);
void setValue(const char* val, char* var);
void setValue(const char* val, u8* var);
void setValue(const char* val, u16* var);
void setValue(const char* val, s16* var);
void setValue(const char* val, u64* var);
void setValue(const char* val, s64* var);
void setValue(const char* val, double* var);

template<int N>
inline void toString(std::string& dst, CharBuffer<N>* var)
{
    assert(var);
    dst = var->getString();
}

template<int N>
inline void setValue(const char* val, CharBuffer<N>* var)
{
    var->setString(val);
}
}


#pragma warning(push)
#pragma warning(disable:4996)

inline void StringHelper::toString(std::string& dst, uString* var)
{
    assert(var);
    dst = var->c_str();
}

inline void StringHelper::toString(std::string& dst, string* var)
{
    assert(var);
    dst = var->c_str();
}


inline void StringHelper::toString(std::string& dst, bool* var)
{
    dst = (*var) ? "true" : "false";
}


inline void StringHelper::setValue(const char* val, uString* var)
{
    assert(val);
    *var = val;
}
inline void StringHelper::setValue(const char* val, string* var)
{
    assert(val);
    *var = val;
}

inline void StringHelper::setValue(const char* val, int* var)
{
    if (val == nullptr)
        *var = 0;
    else if (strlen(val) == 0)
        *var = 0;
    else
        *var = stoi(val);
}

inline void StringHelper::setValue(const char* val, float* var)
{
    *var = stof(val);
}

inline void StringHelper::setValue(const char* val, bool* var)
{
    *var = !strcmp("True", val) || !strcmp("true", val);
}

inline void StringHelper::setValue(const char* val, unsigned int* var)
{
    assert(val);
    sscanf_s(val, "%u", var);
}

inline void StringHelper::setValue(const char* val, long* var)
{
    *var = stol(val);
}

inline void StringHelper::setValue(const char* val, char* var)
{
    *var = val[0];
}

inline void StringHelper::setValue(const char* val, u8* var)
{
    *var = (u8)stoi(val);
}

inline void StringHelper::setValue(const char* val, u16* var)
{
    *var = (u16)stoi(val);
}
inline void StringHelper::setValue(const char* val, u64* var)
{
    *var = (u64)stoll(val);
}
inline void StringHelper::setValue(const char* val, double* var)
{
    *var = stod(val);
}
inline void StringHelper::setValue(const char* val, s16* var)
{
    *var = (s16)stoi(val);
}
inline void StringHelper::setValue(const char* val, s64* var)
{
    *var = (s64)stold(val);
}

#pragma warning(pop)
}
#endif // StringHelper_h__
