#pragma once
#include "mysql.h"
//ID   INT              NOT NULL,
//SALARY   DECIMAL(18, 2) DEFAULT 5000.00,
//PRIMARY KEY(ID)
struct DBColumn
{
    const char* name = nullptr;
    enum_field_types type = enum_field_types::MYSQL_TYPE_DECIMAL;
    u16 length = 0;
    bool autoIncrement = false;
    bool canNull = false;
    Value defaultValue;
};

class COREAPI DBTableDefine
{
public:
    ~DBTableDefine();
    DBTableDefine(const DBTableDefine& def);
    DBTableDefine(const char* name, bool isGlobal, const char* key1, const char* key2, const initializer_list<DBColumn>& array);
    bool generateCreateTableString(stringstream& cmd)const;
    const char* tableName() const;
    const char* key2() const;
    const char* key() const;
    const char* column(int index) const;
private:
    void generateName();
private:
    bool isGlobal;
    string primaryKey1;
    string primaryKey2;
    vector<DBColumn> columns;
    bool globalTable_ = false;
    string tableName_;
    string finalName_;
};

