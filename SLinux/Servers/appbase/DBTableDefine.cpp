#include "stdafx.h"
#include "DBTableDefine.h"
#include "SQLHelper.h"
#include "ServerID.h"

DBTableDefine::~DBTableDefine()
{
}

inline DBTableDefine::DBTableDefine(const DBTableDefine& def)
    : columns_(def.columns_)
{
    this->tableName_ = def.tableName_;
    this->primaryKey1_ = def.primaryKey1_;
    this->primaryKey2_ = def.primaryKey2_;
    this->isGlobal_ = def.isGlobal_;
    generateName();
}

DBTableDefine::DBTableDefine(const char* name, bool isGlobal, const char* key1, const char* key2, const vector<DBColumn>& array)
    : columns_(array)
{
    this->isGlobal_ = isGlobal;
    tableName_ = name;
    primaryKey1_ = key1;
    if (key2 != nullptr)
        primaryKey2_ = key2;
    generateName();
}

bool DBTableDefine::generateCreateTableString(stringstream& cmd) const
{
    cmd << "create table ";
    cmd << tableName() << "(";
    for (auto column : this->columns_)
    {
        cmd << column.name << " ";
        cmd << SQLHelper::getSQLType(column.type) << " ";
        if (column.length > 0)
            cmd << "(" << column.length << ")";
        if (!column.canNull)
            cmd << " not null";
        if (column.autoIncrement)
            cmd << " auto_increment";
        cmd << ",";
    }
    if (this->primaryKey2_.length() > 0)
        cmd << "primary key (" << this->primaryKey1_ << "," << this->primaryKey2_ << ")";
    else
        cmd << "primary key (" << this->primaryKey1_ << ")";

    cmd << ");";
    return true;
}

void DBTableDefine::generateDropCloumnString(stringstream& cmd, string column) const
{
    cmd << "ALTER TABLE " << this->finalName_ << " DROP COLUMN " << column << ";";
}

bool DBTableDefine::generateAddCloumnString(stringstream& cmd, string pre, string column) const
{
    auto columnDefine = std::find_if( this->columns_.begin(), this->columns_.end(), [column](const DBColumn it)
    {
        return column == it.name;
    });

    if (columnDefine == this->columns_.end())
        return false;
    cmd << "ALTER TABLE " << this->finalName_ << " ADD COLUMN " << column << " ";
    cmd << SQLHelper::getSQLType(columnDefine->type) << " ";
    if (columnDefine->length > 0)
        cmd << "(" << columnDefine->length << ")";
    if (!columnDefine->canNull)
        cmd << " not null";
    if (columnDefine->autoIncrement)
        cmd << " auto_increment";

    if(pre.length() == 0)
        cmd << " FIRST ";
    else
        cmd << " AFTER " << pre << " ";
    if (this->primaryKey1_ == columnDefine->name)
        cmd << " add primary key(" << columnDefine->name << ")";
    cmd << ";";
    return true;
}

const char* DBTableDefine::tableName() const
{
    return finalName_.c_str();
}

const char* DBTableDefine::key2() const
{
    return primaryKey2_.c_str();
}

const char* DBTableDefine::key() const
{
    return primaryKey1_.c_str();
}

const char* DBTableDefine::column(int index) const
{
    assert(index < columns_.size());
    return columns_[index].name;
}

const vector<DBColumn>& DBTableDefine::columns() const
{
    return this->columns_;
}

void DBTableDefine::generateName()
{
    finalName_.clear();
    finalName_ += tableName_;
    if (!isGlobal_)
        finalName_ += ServerID::get();
}
