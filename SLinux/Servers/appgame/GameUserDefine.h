#pragma once
#include "DBDefine.h"
#include "CharBuffer.h"
#include "DBTableDefine.h"
#include "ServerID.h"

class GameUserDefine :
    public DBDefine
{
public:
    static const DBTableDefine& GetDefine()
    {
		static const vector<DBColumn> columns =
		{
			{ "id",enum_field_types::MYSQL_TYPE_LONG,0,false,false,0 },
			{ "role",enum_field_types::MYSQL_TYPE_LONG,0,false,false,0 },
		};
		static const DBTableDefine TheTable =
		{
			"game_user",false,"id",nullptr,columns,
		};

        return TheTable;
    };
public:
    int role;
public:
    virtual const char* key() override
    {
        return GetDefine().key();
    }
    virtual const char* table() override
    {
        return GetDefine().tableName();
    }
    virtual void deserializeMe() override
    {
        stream() >> id;

        stream() >> role;
    }

    virtual void serializeMe() override
    {
        stream() << id;

        stream() << role;
    }

    virtual void serializeForUpdate(stringstream& ss) override
    {
        startConcat(ss, GetDefine(), id);
        concat(ss, GetDefine(), role);
    }
};