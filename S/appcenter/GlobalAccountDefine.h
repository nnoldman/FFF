#pragma once
#include "DBDefine.h"
#include "CharBuffer.h"
#include "DBTableDefine.h"

class GlobalAccountDefine :
    public DBDefine
{
public:
    static const DBTableDefine& GetDefine()
    {
        static const DBTableDefine TheTable
        {
            "global_account",true,"id","user",
            {
                { "id",enum_field_types::MYSQL_TYPE_LONG,0,true,false },
                { "user",enum_field_types::MYSQL_TYPE_VARCHAR,Default::NameSize,false,false },
                { "password",enum_field_types::MYSQL_TYPE_VARCHAR,Default::NameSize,false,false },
                { "late_serverid1",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
                { "late_serverid2",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
                { "late_serverid3",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
            },
        };
        return TheTable;
    }



public:
    CharBuffer<Default::NameSize> user;
    CharBuffer<Default::NameSize> password;
    int late_serverid1;
    int late_serverid2;
    int late_serverid3;
public:
    virtual const char* table() override
    {
        return GetDefine().tableName();
    }

    virtual const char* key() override
    {
        return GetDefine().key2();
    }

    virtual void deserializeMe() override
    {
        stream() >> id;
        stream() >> user;
        stream() >> password;
        stream() >> late_serverid1;
        stream() >> late_serverid2;
        stream() >> late_serverid3;
    }

    virtual void serializeMe() override
    {
        stream() << id;
        stream() << user;
        stream() << password;
        stream() << late_serverid1;
        stream() << late_serverid2;
        stream() << late_serverid3;
    }
    virtual void serializeForUpdate(stringstream& ss) override
    {
        startConcat(ss, GetDefine(), id);
        concat(ss, GetDefine(), user);
        concat(ss, GetDefine(), password);
        concat(ss, GetDefine(), late_serverid1);
        concat(ss, GetDefine(), late_serverid2);
        concat(ss, GetDefine(), late_serverid3);
    }
};

