#pragma once
#include <list>
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

    template<int N>
    inline DBStream& operator << (Basic::CharBuffer<N>& var);
    template<int N>
    inline DBStream& operator >> (Basic::CharBuffer<N>& var);
    void set(vector<string>& values);

    const vector<string>& getContents() const
    {
        return contents_;
    }
    void moveToEnd()
    {
        this->position_ = this->contents_.size() - 1;
    }
    void clear()
    {
        this->contents_.clear();
    }
private:
    std::vector<string> contents_;
    int position_;
};

template<int N>
inline DBStream& DBStream::operator >> (Basic::CharBuffer<N>& var)
{
    string container = contents_[position_];
    var.setString(container.c_str());
    contents_.pop_back();
    position_--;
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

