#pragma once
#include "DBDefine.h"
#include "Basic/CharBuffer.h"
#include "DBTableDefine.h"
#include "Basic/ServerID.h"

class GameUserDefine :
    public DBDefineInterface<GameUserDefine> {
  public:
    static const DBTableDefine& GetDefine() {
        static const vector<DBColumn> columns = {
            { "id", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "role", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
        };
        static const DBTableDefine TheTable = {
            "game_user", false, "id", nullptr, columns,
        };
        return TheTable;
    };
  public:
    int role;
  protected:
    virtual void serializeMe() override {
        stream() << id;
        stream() << role;
    }
    virtual void deserializeMe() override {
        stream() >> id;
        stream() >> role;
    }
};
