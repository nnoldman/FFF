#pragma once
#include "DBDefine.h"
#include "DBTableDefine.h"
#include "GameDefine.h"

class BagDefine :
    public DBDefine
{
public:
    static const DBTableDefine& GetDefine()
    {
        static const DBTableDefine TheTable
        {
            "bag",false,"id",nullptr,
            {
                { "id",enum_field_types::MYSQL_TYPE_LONG,0,false,false },
                { "ids",enum_field_types::MYSQL_TYPE_VARCHAR,GameDefine::Capcity::BagLimit * 4,false,false,0 },
            },
        };

        return TheTable;
    }

    virtual const char* table() override
    {
        return GetDefine().tableName();
    }
public:
    int ids[GameDefine::Capcity::BagLimit];
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
        for (int i = 0; i < GameDefine::Capcity::BagLimit; ++i)
            concat(ss, GetDefine(), ids[i]);
    }

    virtual void deserializeMe() override
    {
        for (int i = 0; i < GameDefine::Capcity::BagLimit; ++i)
            stream()>>ids[i];
    }

    virtual void serializeMe() override
    {
        for (int i = 0; i < GameDefine::Capcity::BagLimit; ++i)
            stream() << ids[i];
    }
};


