#pragma once
#include <list>
#include <sstream>
#include "Math.h"
class COREAPI DBStream
{
public:
    DBStream();
    ~DBStream();
    DBStream& operator << (u8 var);
    DBStream& operator << (u16 var);
    DBStream& operator << (u32 var);
    DBStream& operator << (u64 var);
    DBStream& operator << (char var);
    DBStream& operator << (s16 var);
    DBStream& operator << (int var);
    DBStream& operator << (s64 var);
    DBStream& operator << (bool var);
    DBStream& operator << (string var);
    DBStream& operator << (float var);
    DBStream& operator << (double var);
    DBStream& operator << (stringstream& var);

    DBStream& operator >> (u8& var);
    DBStream& operator >> (u16& var);
    DBStream& operator >> (u32& var);
    DBStream& operator >> (u64& var);
    DBStream& operator >> (char& var);
    DBStream& operator >> (s16& var);
    DBStream& operator >> (int& var);
    DBStream& operator >> (s64& var);
    DBStream& operator >> (bool& var);
    DBStream& operator >> (string& var);
    DBStream& operator >> (float& var);
    DBStream& operator >> (double& var);
    DBStream& operator >> (stringstream& var);

    template<typename T, int N>
    DBStream& operator << (const T(&var)[N]);
    template<typename T, int N>
    DBStream& operator >> (T(&var)[N]);


    template<int N>
    inline DBStream& operator << (Basic::CharBuffer<N>& var);
    template<int N>
    inline DBStream& operator >> (Basic::CharBuffer<N>& var);
    void set(vector<string>& values);

    const vector<string>& getContents() const
    {
        return contents_;
    }
    void clear()
    {
        this->contents_.clear();
    }
    void reposition()
    {
        this->position_ = 0;
    }
private:
    std::vector<string> contents_;
    ::size_t position_;
};

template<int N>
inline DBStream& DBStream::operator >> (Basic::CharBuffer<N>& var)
{
    string container = contents_[position_];
    var.setString(container.c_str());
    position_++;
    return *this;
}

template<typename T, int N>
DBStream& DBStream::operator>>(T(&var)[N])
{
    string container = contents_[position_];
    Basic::Math::fromHEX(var, container);
    position_++;
    return *this;
}

template<typename T, int N>
DBStream& DBStream::operator<<(const T(&var)[N])
{
    string buffer;
    stringstream ss;
    Basic::Math::toHEX(var, buffer);
    ss << "'" << buffer << "'";
    contents_.push_back(ss.str());
    position_++;
    return *this;
}

template<int N>
inline DBStream& DBStream::operator<<(Basic::CharBuffer<N>& var)
{
    string container = var.c_str();
    stringstream ss;
    ss << "'" << container << "'";
    contents_.push_back(ss.str());
    position_++;
    return *this;
}

