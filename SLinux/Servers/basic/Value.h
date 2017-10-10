#pragma once
#include <string>
#include <sstream>
using namespace std;
namespace Basic
{
    enum ValueType
    {
		Empty,
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
			return (this->type_ == ValueType::String&& this->string_) ? this->string_->c_str() : nullptr;
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
		void setString(const char* var);
		
    private:
        ValueType type_;
        union
        {
            u8 u8_;
            u16 u16_;
            u32 u32_;
            u64 u64_;

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
		this->type_ = ValueType::Empty;
		this->u64_ = 0;
		this->string_ = nullptr;
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
		this->setString(var.c_str());
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
		:u64_(0)
	{
        this->type_ = var.type_;
		if (this->type_ == ValueType::String)
			this->setString((*var.string_).c_str());
		else
			this->u64_ = var.u64_;
    }

    inline Value::Value(const char* var)
		:u64_(0)
	{
		this->type_ = ValueType::String;
		this->setString(var);
	}

    inline Value& Value::operator=(const char* var)
    {
		this->type_ = ValueType::String;
		this->setString(var);
        return *this;
    }

    inline std::string Value::toString()
    {
        stringstream ss;
        switch (type_)
        {
        case U8:
        {
            ss << u8_;
        }
        break;
        case U16:
        {
            ss << u16_;
        }
        break;
        case U32:
        {
            ss << u32_;
        }
        break;
        case U64:
        {
            ss << u64_;
        }
        break;
        case S8:
        {
            ss << char_;
        }
        break;
        case S16:
        {
            ss << s16_;
        }
        break;
        case S32:
        {
            ss << s32_;
        }
        break;
        case S64:
        {
            ss << s64_;
        }
        break;
        case Bool:
        {
            ss << true;
        }
        break;
        case Float:
        {
            ss << float_;
        }
        break;
        case Double:
        {
            ss << double_;
        }
        break;
        case String:
        {
            ss << string_->c_str();
        }
        break;
        default:
            break;
        }
        return ss.str();
    }

	inline void Value::setString(const char* var)
	{
		if (this->type_ == ValueType::String)
			dSafeDelete(this->string_);
		this->string_ = new string();
		*this->string_ = var;
	}

	inline Basic::Value::~Value()
    {
        if (this->type_ == ValueType::String)
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
		this->setString(var.c_str());
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

