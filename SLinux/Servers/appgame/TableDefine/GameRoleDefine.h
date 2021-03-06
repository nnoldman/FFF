#ifndef GameRoleDefine_h__
#define GameRoleDefine_h__

#include "CharBuffer.h"
#include "RoleInfoDefine.h"
#include "Default.h"
#include "../../appbase/db/DBDefine.h"

class GameRoleDefine :
    public DBDefineInterface<GameRoleDefine> {
  public:
    static const DBTableDefine& GetDefine() {
        static const vector<DBColumn> columns = {
            { "id", enum_field_types::MYSQL_TYPE_LONG, 0, true, false, 0 },
            { "name", enum_field_types::MYSQL_TYPE_VARCHAR, Default::NameSize, false, false, "" },
            { "vip", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "level", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 1 },
            { "sex", enum_field_types::MYSQL_TYPE_BIT, 0, false, false, 0 },
            { "job", enum_field_types::MYSQL_TYPE_SHORT, 0, false, false, 0 },
            { "borntime", enum_field_types::MYSQL_TYPE_DATETIME, 0, false, false, 0 },
            { "functions", enum_field_types::MYSQL_TYPE_VARCHAR, GameDefine::Capcity::Function / 4, false, false, 0 },
        };
        static const DBTableDefine TheTable = {
            "game_role", false, "id", "name", columns,
        };
        return TheTable;
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
    virtual void deserializeMe() override {
        stream() >> id;
        stream() >> base.name;
        stream() >> base.vip;
        stream() >> base.level;
        stream() >> base.sex;
        stream() >> base.job;
        stream() >> base.borntime;
        stream() >> base.functions;
    }

    virtual void serializeMe() override {
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


#endif // GameRoleDefine_h__
