#pragma once
#include "DBDefine.h"
#include "CharBuffer.h"
#include "DBTableDefine.h"

class GameRoleDefine :
    public DBDefine
{
public:
    static const DBTableDefine& GetDefine()
    {
        static const DBTableDefine TheTable
        {
            "game_role",false,"id","name",
            {
                { "id",enum_field_types::MYSQL_TYPE_LONG,0,true,false },
                { "name",enum_field_types::MYSQL_TYPE_VARCHAR,Default::NameSize,false,false },
                { "vip",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
                { "level",enum_field_types::MYSQL_TYPE_LONG,0,false,false,1 },
                { "sex",enum_field_types::MYSQL_TYPE_BIT,0,false,false },
                { "job",enum_field_types::MYSQL_TYPE_SHORT,0,false,false },
            },
        };
        return TheTable;
    }

    virtual const char* table() override
    {
        return GetDefine().tableName();
    }
public:
    CharBuffer<Default::NameSize> name;
    int vip;
    int level;
    int sex;
    int job;
public:
    virtual const char* key() override
    {
        return GetDefine().key();
    }
    virtual const char* key2() override
    {
        return GetDefine().key2();
    }
    virtual void serializeForUpdate(stringstream& ss) override
    {
        startConcat(ss, GetDefine(), id);
        concat(ss, GetDefine(), name);
        concat(ss, GetDefine(), vip);
        concat(ss, GetDefine(), level);
        concat(ss, GetDefine(), sex);
        concat(ss, GetDefine(), job);
    }

    virtual void deserializeMe() override
    {
        stream() >> id;
        stream() >> name;
        stream() >> vip;
        stream() >> level;
        stream() >> sex;
        stream() >> job;
    }

    virtual void serializeMe() override
    {
        stream() << id;
        stream() << name;
        stream() << vip;
        stream() << level;
        stream() << sex;
        stream() << job;
    }
};


