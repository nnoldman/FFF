#pragma once
#include <string>
using namespace std;
namespace Basic
{

enum ValueType
{
    U8,
    U16,
    U32,
    U64,
    S8,
    S16,
    S32,
    S64,
    Bool,
    Float,
    Double,
    CharArray,
    String,
};

class Value
{
public:
    Value();
    ~Value();
    Value(const Value& var);
    Value(u8 var);
    Value(u16 var);
    Value(u32 var);
    Value(u64 var);

    Value(s16 var);
    Value(int var);
    Value(s64 var);

    Value(bool var);
    Value(char var);
    Value(string var);

    Value(float var);
    Value(double var);
    Value(const char* var);

    Value& operator=(u8 var);
    Value& operator=(u16 var);
    Value& operator=(u32 var);
    Value& operator=(u64 var);
    Value& operator=(s16 var);
    Value& operator=(int var);
    Value& operator=(s64 var);
    Value& operator=(bool var);
    Value& operator=(char var);
    Value& operator=(string var);
    Value& operator=(float var);
    Value& operator=(double var);
    Value& operator=(const char* var);


    operator u8()
    {
        return this->u8_;
    }
    operator u16()
    {
        return this->u16_;
    }
    operator u32()
    {
        return this->u32_;
    }
    operator u64()
    {
        return this->u64_;
    }
    operator s16()
    {
        return this->s16_;
    }
    operator int()
    {
        return this->s32_;
    }
    operator s64()
    {
        return this->s64_;
    }
    operator bool()
    {
        return this->bool_;
    }
    operator char()
    {
        return this->char_;
    }
    operator const char* ()
    {
        return this->string_ ? this->string_->c_str() : nullptr;
    }
    operator float()
    {
        return this->float_;
    }
    operator double()
    {
        return this->double_;
    }

    string toString();
    inline ValueType type() const
    {
        return type_;
    }
private:
    ValueType type_;
    union
    {
        u8 u8_;
        u16 u16_;
        u32 u32_;
        u32 u64_;

        char char_;
        s16 s16_;
        s32 s32_;
        s64 s64_;

        bool bool_;
        string* string_;
        float float_;
        double double_;
    };
};
}


namespace Basic
{
inline Value::Value()
{
}

inline Value::Value(int var)
{
    this->s32_ = var;
    type_ = ValueType::S32;
}

inline Value::Value(char var)
{
    this->char_ = var;
    type_ = ValueType::S8;
}

inline Value::Value(u16 var)
{
    this->u16_ = var;
    type_ = ValueType::U16;
}

inline Value::Value(u32 var)
{
    this->u32_ = var;
    type_ = ValueType::U32;
}

inline Value::Value(string var)
{
    this->string_ = new string();
    *this->string_ = var;
    this->type_ = ValueType::String;
}

inline Value::Value(bool var)
{
    this->bool_ = var;
    type_ = ValueType::Bool;
}

inline Value::Value(u64 var)
{
    this->u64_ = var;
    type_ = ValueType::U64;
}

inline Value::Value(s16 var)
{
    this->s16_ = var;
    type_ = ValueType::S16;
}


inline Value::Value(s64 var)
{
    this->s64_ = var;
    type_ = ValueType::S64;
}

inline Value::Value(float var)
{
    this->float_ = var;
    type_ = ValueType::Float;
}

inline Value::Value(double var)
{
    this->double_ = var;
    type_ = ValueType::Double;
}

inline Value::Value(u8 var)
{
    this->u8_ = var;
    type_ = ValueType::U8;
}

inline Value::Value(const Value& var)
{
    this->u64_ = var.u64_;
    this->double_ = var.double_;
    this->type_ = var.type_;
    if (this->type_ == ValueType::String)
    {
        this->string_ = new string();
        if (var.string_)
            *this->string_ = *var.string_;
    }
}

inline Value::Value(const char* var)
{
    this->string_ = new string();
    *this->string_ = var;
    this->type_ = ValueType::String;
}

inline Value& Value::operator=(const char* var)
{
    this->string_ = new string();
    *this->string_ = var;
    this->type_ = ValueType::String;
    return *this;
}

inline std::string Value::toString()
{
    char buffer[_CVTBUFSIZE] = { 0 };
    switch (type_)
    {
    case U8:
        {
            _itoa_s(u8_, buffer, 10);
        }
        break;
    case U16:
        {
            _itoa_s(u16_, buffer, 10);
        }
        break;
    case U32:
        {
            _ultoa_s(u32_, buffer, 10);
        }
        break;
    case U64:
        {
            _ui64toa_s(u64_, buffer, _CVTBUFSIZE, 10);
        }
        break;
    case S8:
        {
            _itoa_s(char_, buffer, 10);
        }
        break;
    case S16:
        {
            _itoa_s(s16_, buffer, 10);
        }
        break;
    case S32:
        {
            _itoa_s(s32_, buffer, 10);
        }
        break;
    case S64:
        {
            _i64toa_s(s64_, buffer, _CVTBUFSIZE, 10);
        }
        break;
    case Bool:
        {
            if (bool_)
                strcpy_s(buffer, "true");
            else
                strcpy_s(buffer, "false");
        }
        break;
    case Float:
        {
            int decimal;
            int sign;
            _fcvt_s(buffer, float_, _CVTBUFSIZE, 5, &decimal, &sign);
        }
        break;
    case Double:
        {
            _gcvt_s(buffer, _CVTBUFSIZE, double_, 5);
        }
        break;
    case String:
        {
            if (this->string_)
                strcpy_s(buffer, string_->c_str());
        }
        break;
    default:
        break;
    }
    return buffer;
}

inline Basic::Value::~Value()
{
    if (this->type_ == ValueType::String && this->string_)
    {
        dSafeDelete(this->string_);
    }
}

inline Basic::Value& Basic::Value::operator=(double var)
{
    this->double_ = var;
    type_ = ValueType::Double;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(float var)
{
    this->float_ = var;
    type_ = ValueType::Float;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(string var)
{
    if (this->string_ == nullptr)
    {
        this->string_ = new string();
    }
    *this->string_ = var;
    this->type_ = ValueType::String;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(char var)
{
    this->char_ = var;
    type_ = ValueType::S8;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(bool var)
{
    this->bool_ = var;
    type_ = ValueType::Bool;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(s64 var)
{
    this->s64_ = var;
    type_ = ValueType::S64;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(int var)
{
    this->s32_ = var;
    type_ = ValueType::S32;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(s16 var)
{
    this->u16_ = var;
    type_ = ValueType::U16;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(u64 var)
{
    this->u64_ = var;
    type_ = ValueType::U64;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(u32 var)
{
    this->u32_ = var;
    type_ = ValueType::U32;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(u16 var)
{
    this->u16_ = var;
    type_ = ValueType::U16;
    return *this;
}

inline Basic::Value& Basic::Value::operator=(u8 var)
{
    this->u8_ = var;
    type_ = ValueType::U8;
    return *this;
}

}

