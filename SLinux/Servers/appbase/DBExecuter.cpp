#include "stdafx.h"
#include "DBExecuter.h"
#include "DBTableDefine.h"
#include "DBDefine.h"

bool DBExecuter::initialize(const DBConfig & config) {
    config_ = config;
    return true;
}
bool DBExecuter::pullByKey1(OUT DBDefine* def) {
    assert(def->key2() == nullptr || strlen(def->key2()) == 0);
    return this->pull(def->key(),def->id, def);
}

bool DBExecuter::pullByKey1Key2(DBDefine* def, Basic::AnyValue keyvalue) {
    stringstream cmd;
    cmd << "SELECT * FROM " << def->table() << " WHERE " << def->key() << "=" << def->id <<
        " and "<<def->key2()<<"="<<makeValue(keyvalue)<<";";
    return query(cmd.str().c_str(), def);
}

bool DBExecuter::pull(const char* key, Basic::AnyValue keyvalue, OUT DBDefine* def) {
    stringstream ss;
    ss << "SELECT * FROM " << def->table() << " WHERE " << key << "=" << makeValue(keyvalue) << ";";
    return query(ss.str().c_str(), def);
}

bool DBExecuter::pullByKey1(const DBTableDefine& def, Basic::AnyValue keyvalue, DBDefineCreator creator, OUT std::vector<DBDefine*>& ret) {
    ret.clear();
    stringstream ss;
    ss << "SELECT * FROM " << def.tableName() << " WHERE " << def.key() << "=" << makeValue(keyvalue) << ";";
    return query(ss.str().c_str(), ret, creator);
}


bool DBExecuter::commitByKey1(DBDefine* def) {
    deleteByKey1(def);
    return insert(def);
}


bool DBExecuter::commitByKey1Key2(DBDefine* def, Basic::AnyValue key2Value) {
    deleteByKey1Key2(def, key2Value);
    return insert(def);
}

bool DBExecuter::deleteByKey1(DBDefine* def) {
    assert(def->key2() == nullptr || strlen(def->key2()) == 0);
    stringstream cmd;
    cmd << "DELETE FROM " << def->table() << " WHERE id=" << def->id << ";";
    return this->query(cmd.str().c_str());
}

bool DBExecuter::deleteByKey1Key2(DBDefine* def, Basic::AnyValue key2Value) {
    //assert(def->key2() != nullptr);
    stringstream cmd;
    cmd << "DELETE FROM " << def->table() << " WHERE id=" << def->id << " AND " << def->key2() << "=" << makeValue(key2Value) << ";";
    return this->query(cmd.str().c_str());
}

bool DBExecuter::insert(OUT DBDefine* def) {
    stringstream ss;
    stringstream ssvalue;
    def->serialize(ssvalue);
    ss << "INSERT INTO " << def->table() << " VALUES (" << ssvalue.str().c_str() << ");";
    return this->query(ss.str().c_str());
}

string DBExecuter::makeValue(const Basic::AnyValue& keyvalue) {
    stringstream ret;
    if (keyvalue.isString()) {
        ret << "'" << keyvalue.get<string>() << "'";
    } else {
        ret << keyvalue.toString();
    }
    return ret.str();
}

bool DBExecuter::insertAndQuery(Basic::AnyValue keyvalue, OUT DBDefine* def) {
    bool ret = this->insert(def);
    if (ret) {
        ret = this->pull(def->key(),keyvalue, def);
    }
    return ret;
}

bool DBExecuter::insertAndQuery(const char* key, Basic::AnyValue keyvalue, OUT DBDefine* def) {
    bool ret = this->insert(def);
    if (ret) {
        ret = this->pull(key, keyvalue, def);
    }
    return ret;
}

const DBConfig& DBExecuter::config() const {
    return this->config_;
}
