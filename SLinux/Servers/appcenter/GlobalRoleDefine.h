#pragma once
#include "Default.h"
#include "CharBuffer.h"

class GlobalRoleDefine : public DBDefine {
  public:
    static const DBTableDefine& GetDefine() {
        static const vector<DBColumn> columns = {
            { "id",enum_field_types::MYSQL_TYPE_LONG,0,true,false,0 },
            { "name",enum_field_types::MYSQL_TYPE_VARCHAR,Default::NameSize,false,false,"" },
            { "level",enum_field_types::MYSQL_TYPE_LONG,0,false,false,0 },
            { "vip",enum_field_types::MYSQL_TYPE_LONG,0,false,false,0 },
        };
        static const DBTableDefine TheTable = {
            "global_role",true,"id","name",columns,
        };
        return TheTable;
    }
  public:
    CharBuffer<Default::NameSize> name;
    int level;
    int vip;
  protected:
    virtual void deserializeMe() override {
        stream() >> id;
        stream() >> level;
        stream() >> name;
        stream() >> vip;
    }
    virtual void serializeMe() override {
        stream() << id;
        stream() << level;
        stream() << name;
        stream() << vip;
    }
};

