#ifndef MailDefine_h__
#define MailDefine_h__

#include "DBDefine.h"
#include "DBTableDefine.h"
#include "GameDefine.pb.h"
#include "RoleInfoDefine.h"

class MailDefine :
    public DBDefineInterface<MailDefine> {
  public:
    static const DBTableDefine& GetDefine() {
        static const vector<DBColumn> columns = {
            { "id", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "dbID", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "itemID", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "itemCount", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "money", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "gold", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "time", enum_field_types::MYSQL_TYPE_DATETIME, 0, false, false, 0 },
            { "sender", enum_field_types::MYSQL_TYPE_VARCHAR, Default::NameSize, false, false, "" },
            { "content", enum_field_types::MYSQL_TYPE_VARCHAR, Default::DataSize, false, false, "" },
        };
        static const DBTableDefine TheTable = {
            "game_mail", false, "id", "dbID", columns,
        };
        return TheTable;
    }
  public:
    int dbID;
    int itemID;
    int itemCount;
    int money;
    int gold;
    Basic::CharBuffer<Default::TimeSize> time;
    Basic::CharBuffer<Default::NameSize> sender;
    Basic::CharBuffer<Default::DataSize> content;
  public:
    virtual void deserializeMe() override {
        stream() >> this->id;
        stream() >> this->dbID;
        stream() >> this->itemID;
        stream() >> this->itemCount;
        stream() >> this->money;
        stream() >> this->gold;
        stream() >> this->time;
        stream() >> this->sender;
        stream() >> this->content;
    }
    virtual void serializeMe() override {
        stream() << this->id;
        stream() << this->dbID;
        stream() << this->itemID;
        stream() << this->itemCount;
        stream() << this->money;
        stream() << this->gold;
        stream() << this->time;
        stream() << this->sender;
        stream() << this->content;
    }
};

#endif // MailDefine_h__
