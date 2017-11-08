#pragma once
#include "CharBuffer.h"
#include "DBTableDefine.h"
#include "RoleInfoDefine.h"
#include "DBDefine.h"
#include "Default.h"

class GameRoleDefine :
    public DBDefine
{
public:
    static const DBTableDefine& GetDefine()
    {
        static const vector<DBColumn> columns =
        {
            { "id", enum_field_types::MYSQL_TYPE_LONG, 0, true, false, 0 },
            { "name", enum_field_types::MYSQL_TYPE_VARCHAR, Default::NameSize, false, false, "" },
            { "vip", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "level", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 1 },
            { "sex", enum_field_types::MYSQL_TYPE_BIT, 0, false, false, 0 },
            { "job", enum_field_types::MYSQL_TYPE_SHORT, 0, false, false, 0 },
            { "borntime", enum_field_types::MYSQL_TYPE_DATETIME, 0, false, false, 0 },
            { "functions", enum_field_types::MYSQL_TYPE_VARCHAR, GameDefine::Capcity::Function / 4, false, false, 0 },
        };
        static const DBTableDefine TheTable =
        {
            "game_role", false, "id", "name", columns,
        };
        return TheTable;
    }

    virtual const char* table() override
    {
        return GetDefine().tableName();
    }

public://游戏基本系统
    RoleStat::Base base;
    RoleStat::Property property;
    RoleStat::Mail mail;

public://游戏内容
    RoleStat::Env env;
    RoleStat::Member member;
    RoleStat::Group group;
    RoleStat::Awareness awareness;
    RoleStat::Gene gene;
    RoleStat::MileStone mileStone;
    RoleStat::Teachnology teachnology;

public:
    virtual const char* key() override
    {
        return GetDefine().key();
    }
    virtual const char* key2() override
    {
        return GetDefine().key2();
    }
    virtual void deserializeMe() override
    {
        stream() >> id;
        stream() >> base.name;
        stream() >> base.vip;
        stream() >> base.level;
        stream() >> base.sex;
        stream() >> base.job;
        stream() >> base.borntime;
        stream() >> base.functions;
    }

    virtual void serializeMe() override
    {
        stream() << id;
        stream() << base.name;
        stream() << base.vip;
        stream() << base.level;
        stream() << base.sex;
        stream() << base.job;
        stream() << base.borntime;
        stream() << base.functions;
    }
};


