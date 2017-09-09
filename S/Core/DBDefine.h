#pragma once
class DataBase;
#include "DBStream.h"
#include "Value.h"
#include "ServerID.h"
#include "DBTableDefine.h"
class COREAPI DBDefine
{
public:
    int id;
public:
    virtual ~DBDefine() {}
    virtual const char* table() = 0;

    void setGlobalID(int id);
    virtual const char* key() = 0;
    virtual const char* key2();

    virtual void deserialize() final;
    virtual void serialize() final;
    virtual void serializeForUpdate(stringstream& ss) = 0;

    virtual void serializeMe() = 0;
    virtual void deserializeMe() = 0;

    void set(vector<string>& values);
    //use key()
    bool pull(Value keyvalue);
    //use key()
    bool commit();
    bool insertAndQuery(Value keyvalue);
    bool insertAndQuery(const char* key, Value keyvalue);

    bool getValues(stringstream& ss);
    bool exist(const char* key, Value value);
public:
    inline DBStream& stream()
    {
        return stream_;
    }
protected:
    template<typename T>
    void startConcat(stringstream& ss, const DBTableDefine& def, T& value)
    {
        concatIndex_ = 0;
        ss << def.column(concatIndex_) << "=" << value << Basic::Variable::space;
        concatIndex_++;
    }
    template<int N>
    void startConcat(stringstream& ss, const DBTableDefine& def, CharBuffer<N>& value)
    {
        concatIndex_ = 0;
        ss << def.column(concatIndex_) << "='" << value.c_str() <<"'"<< Basic::Variable::space;
        concatIndex_++;
    }
    template<typename T>
    void concat(stringstream& ss, const DBTableDefine& def,T& value)
    {
        ss << "," << def.column(concatIndex_) << "=" << value << Basic::Variable::space;
        concatIndex_++;
    }
    template<int N>
    void concat(stringstream& ss, const DBTableDefine& def, CharBuffer<N>& value)
    {
        ss << "," << def.column(concatIndex_) << "='" << value.c_str() << "'" << Basic::Variable::space;
        concatIndex_++;
    }
private:
    DBStream stream_;
    int concatIndex_;
};
inline	void DBDefine::setGlobalID(int id)
{
    this->id = id;
}

