#ifndef ItemDefine_h__
#define ItemDefine_h__

#include "DBDefine.h"
#include "DBTableDefine.h"
#include "GameDefine.pb.h"
#include "RoleInfoDefine.h"

class ItemDefine :
    public DBDefine
{
public:
    static const int ObjectsCapacity = GameDefine::Bag + GameDefine::Equip;

    static const DBTableDefine& GetDefine()
    {
        static const vector<DBColumn> columns =
        {
            { "id", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "dbID", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "itemID", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "count", enum_field_types::MYSQL_TYPE_LONG, 0, false, false, 0 },
            { "position", enum_field_types::MYSQL_TYPE_SHORT, 0, false, false, 0 },
            { "cell", enum_field_types::MYSQL_TYPE_TINY, 0, false, false, 0 },
            { "kind", enum_field_types::MYSQL_TYPE_TINY, 0, false, false, 0 },
            { "borntime", enum_field_types::MYSQL_TYPE_DATETIME, 0, false, false, 0 },
        };
        static const DBTableDefine TheTable =
        {
            "items", false, "id", "dbID", columns,
        };
        return TheTable;
    }
    static DBDefine* Create()
    {
        return new ItemDefine();
    }

    virtual const char* table() override
    {
        return GetDefine().tableName();
    }
public:
    int dbID;
    int itemID;
    int count;
    short position;
    char cell;
    char kind;
    Basic::CharBuffer<Default::TimeSize> borntime;
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
        stream() >> this->id;
        stream() >> this->dbID;
        stream() >> this->itemID;
        stream() >> this->count;
        stream() >> this->position;
        stream() >> this->cell;
        stream() >> this->kind;
        stream() >> this->borntime;
    }

    virtual void serializeMe() override
    {
        stream() << this->id;
        stream() << this->dbID;
        stream() << this->itemID;
        stream() << this->count;
        stream() << this->position;
        stream() << this->cell;
        stream() << this->kind;
        stream() << this->borntime;
    }
};

#endif // ItemDefine_h__
