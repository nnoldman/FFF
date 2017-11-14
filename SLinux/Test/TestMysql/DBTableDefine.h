#ifndef DBTableDefine_h__
#define DBTableDefine_h__

#include "mysql/mysql.h"
#include <initializer_list>
struct DBColumn {
    const char* name = nullptr;
    enum_field_types type = enum_field_types::MYSQL_TYPE_DECIMAL;
    u16 length = 0;
    bool autoIncrement = false;
    bool canNull = false;
    Basic::AnyValue defaultValue;

    DBColumn(const char* name, enum_field_types type, u16 length, bool autoIncrement, bool canNull, Basic::AnyValue defaultValue) {
        this->name = name;
        this->type = type;
        this->length = length;
        this->autoIncrement = autoIncrement;
        this->canNull = canNull;
        this->defaultValue = defaultValue;
    }
};

class DBTableDefine {
  public:
    ~DBTableDefine();
    DBTableDefine(const DBTableDefine& def);
    DBTableDefine(const char* name, bool isGlobal, const char* key1, const char* key2, const vector<DBColumn>& array);
    bool generateCreateTableString(stringstream& cmd)const;
    void generateDropCloumnString(stringstream& cmd, string column) const;
    bool generateAddCloumnString(stringstream& cmd, string pre, string column) const;
    const char* tableName() const;
    const char* key2() const;
    const char* key() const;
    const char* column(int index) const;
    const vector<DBColumn>& columns() const;
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

#endif // DBTableDefine_h__
