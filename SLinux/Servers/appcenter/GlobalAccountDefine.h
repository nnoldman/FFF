#pragma once
#include "CharBuffer.h"

class GlobalAccountDefine :
    public DBDefineInterface<GlobalAccountDefine> {
  public:
    static const DBTableDefine& GetDefine() {
        static const vector<DBColumn> columns = {
            { "id", enum_field_types::MYSQL_TYPE_LONG, 0, true, false, 0 },
            { "user", enum_field_types::MYSQL_TYPE_VARCHAR, Default::NameSize, false, false, "" },
            { "password", enum_field_types::MYSQL_TYPE_VARCHAR, Default::NameSize, false, false, "" },
            { "late_serverid1", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0},
            { "late_serverid2", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0},
            { "late_serverid3", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
        };
        static const DBTableDefine TheTable = {
            "global_account", true, "id", "user", columns,
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
    virtual void deserializeMe() override {
        stream() >> id;
        stream() >> user;
        stream() >> password;
        stream() >> late_serverid1;
        stream() >> late_serverid2;
        stream() >> late_serverid3;
    }

    virtual void serializeMe() override {
        stream() << id;
        stream() << user;
        stream() << password;
        stream() << late_serverid1;
        stream() << late_serverid2;
        stream() << late_serverid3;
    }
};

