#pragma once
#include "mysql.h"
//ID   INT              NOT NULL,
//SALARY   DECIMAL(18, 2) DEFAULT 5000.00,
#include <initializer_list>
#include "AnyObject.h"
//PRIMARY KEY(ID)
struct DBColumn
{
    const char* name = nullptr;
    enum_field_types type = enum_field_types::MYSQL_TYPE_DECIMAL;
    u16 length = 0;
    bool autoIncrement = false;
    bool canNull = false;
	AnyObject defaultValue;

    DBColumn(const char* name, enum_field_types type, u16 length, bool autoIncrement, bool canNull, AnyObject defaultValue)
    {
        this->name = name;
        this->type = type;
        this->length = length;
        this->autoIncrement = autoIncrement;
        this->canNull = canNull;
        this->defaultValue = defaultValue;
    }
};

class COREAPI DBTableDefine
{
public:
    ~DBTableDefine();
    DBTableDefine(const DBTableDefine& def);
    DBTableDefine(const char* name, bool isGlobal, const char* key1, const char* key2, const vector<DBColumn>& array);
    bool generateCreateTableString(stringstream& cmd)const;
    const char* tableName() const;
    const char* key2() const;
    const char* key() const;
    const char* column(int index) const;
private:
    void generateName();
private:
    const vector<DBColumn>& columns_;
    bool isGlobal_;
    string primaryKey1_;
    string primaryKey2_;
    string tableName_;
    string finalName_;
};

