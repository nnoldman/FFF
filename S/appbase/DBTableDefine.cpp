#include "stdafx.h"
#include "DBTableDefine.h"
#include "SQLHelper.h"
#include "ServerID.h"

DBTableDefine::~DBTableDefine()
{
}

inline DBTableDefine::DBTableDefine(const DBTableDefine& def)
{
    this->tableName_ = def.tableName_;
    this->primaryKey1 = def.primaryKey1;
    this->primaryKey2 = def.primaryKey2;
    this->columns = def.columns;
    this->isGlobal = def.isGlobal;
    generateName();
}

inline DBTableDefine::DBTableDefine(const char* name, bool isGlobal, const char* key1, const char* key2, const initializer_list<DBColumn>& array)
{
    this->isGlobal = isGlobal;
    tableName_ = name;
    primaryKey1 = key1;
    if (key2 != nullptr)
        primaryKey2 = key2;
    for (auto iter : array)
        columns.push_back(iter);
    generateName();
}

bool DBTableDefine::generateCreateTableString(stringstream& cmd) const
{
    cmd << "create table ";
    cmd << tableName() << "(";
    for (auto column : this->columns)
    {
        cmd << column.name << " ";
        cmd << SQLHelper::getSQLType(column.type)<<" ";
        if (column.length > 0)
            cmd << "(" << column.length << ")";
        if (!column.canNull)
            cmd << " not null";
        if (column.autoIncrement)
            cmd << " auto_increment";
        cmd << ",";
    }
    if (this->primaryKey2.length() > 0)
        cmd << "primary key (" << this->primaryKey1 <<","<< this->primaryKey2 << ")";
    else
        cmd << "primary key (" << this->primaryKey1 << ")";

    cmd << ");";
    return true;
}

const char* DBTableDefine::tableName() const
{
    return finalName_.c_str();
}

const char* DBTableDefine::key2() const
{
    return primaryKey2.c_str();
}

const char* DBTableDefine::key() const
{
    return primaryKey1.c_str();
}

const char* DBTableDefine::column(int index) const
{
    assert(index < columns.size());
    return columns[index].name;
}

void DBTableDefine::generateName()
{
    finalName_.clear();
    finalName_ += tableName_;
    if (!isGlobal)
        finalName_ += ServerID::get();
}
