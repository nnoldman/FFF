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
        static const vector<DBColumn> columns =
        {
            { "id",enum_field_types::MYSQL_TYPE_LONG,0,true,false,0 },
            { "name",enum_field_types::MYSQL_TYPE_VARCHAR,Default::NameSize,false,false,"" },
            { "level",enum_field_types::MYSQL_TYPE_LONG,0,false,false,0 },
            { "vip",enum_field_types::MYSQL_TYPE_LONG,0,false,false,0 },
        };
        static const DBTableDefine TheTable =
        {
            "global_role",true,"id","name",columns,
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

