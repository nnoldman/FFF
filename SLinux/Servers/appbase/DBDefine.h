#pragma once
class DataBase;
#include "DBStream.h"
#include "Value.h"
#include "Variable.h"
#include "ServerID.h"
#include "DBTableDefine.h"
#include "AnyObject.h"
#include "CharBuffer.h"
#include <sstream>
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

    virtual void serializeMe() = 0;
    virtual void deserializeMe() = 0;

    void set(vector<string>& values);
    //use key()
    bool pull(AnyObject keyvalue);
    //use key()
    bool commitByKey1();
    bool commitByKey1Key2(AnyObject key2value);
    bool insertByKey1();
    bool insertByKey1Key2(AnyObject key2value);
    bool insertAndQuery(AnyObject keyvalue);
    bool insertAndQuery(const char* key, AnyObject keyvalue);

    bool getValues(stringstream& ss);
    bool exist(const char* key, AnyObject value);
public:
    inline DBStream& stream()
    {
        return stream_;
    }
private:
    DBStream stream_;
};
inline	void DBDefine::setGlobalID(int id)
{
    this->id = id;
}

template<typename T>
class DBDefineInterface: public DBDefine
{
public:
    static DBDefine* Create()
    {
        return new T();
    }
    virtual const char* table() override
    {
        return T::GetDefine().tableName();
    }
    virtual const char* key() override
    {
        return T::GetDefine().key();
    }
    virtual const char* key2() override
    {
        return T::GetDefine().key2();
    }
};
