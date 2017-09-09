#pragma once
#include "DBDefine.h"
#include "Default.h"
#include "DBStream.h"
#include "CharBuffer.h"
#include "DBTableDefine.h"

class GlobalRoleDefine : public DBDefine
{
public:
    static const DBTableDefine& GetDefine()
    {
        static const DBTableDefine TheTable =
        {
            "global_role",true,"id","name",
            {
                { "id",enum_field_types::MYSQL_TYPE_LONG,0,true,false },
                { "name",enum_field_types::MYSQL_TYPE_VARCHAR,Default::NameSize,false,false },
                { "level",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
                { "vip",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
            },
        };
        return TheTable;
    }
public:
    CharBuffer<Default::NameSize> name;
    int level;
    int vip;

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
        stream() >> level;
        stream() >> name;
        stream() >> vip;
    }

    virtual void serializeMe() override
    {
        stream() << id;
        stream() << level;
        stream() << name;
        stream() << vip;
    }

};

