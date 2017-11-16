#include "stdafx.h"
#include "DBDefine.h"
#include "DataBase.h"

const char* DBDefine::key2() {
    return nullptr;
}

void DBDefine::deserialize(std::vector<string>& columns) {
    this->stream().set(columns);
    this->stream().reposition();
    this->deserializeMe();
}

void DBDefine::serialize(stringstream& columns) {
    this->stream().clear();
    this->serializeMe();
    this->getValues(columns);
}

void DBDefine::set(vector<string>& values) {
    stream_.set(values);
}

bool DBDefine::pullByKey1() {
    return this->execter->pullByKey1(this);
}

bool DBDefine::pullByKey1Key2(Basic::AnyValue key2value) {
    return this->execter->pullByKey1Key2(this,key2value);
}

bool DBDefine::pullByKey(const char* key, Basic::AnyValue value) {
    return this->execter->pull(key, value,this);
}

bool DBDefine::commitByKey1() {
    return this->execter->commitByKey1(this);
}

bool DBDefine::commitByKey1Key2(Basic::AnyValue key2value) {
    return this->execter->commitByKey1Key2(this, key2value);
}

bool DBDefine::insertByKey1() {
    return this->execter->commitByKey1(this);
}

bool DBDefine::insertByKey1Key2(Basic::AnyValue key2value) {
    return this->execter->commitByKey1Key2(this, key2value);
}

//delete from global_account where user = '123';

bool DBDefine::insertAndQuery(const char* key, Basic::AnyValue keyvalue) {
    if (this->execter->commit(this))
        return this->execter->pull(key, keyvalue, this);
    return false;
}

bool DBDefine::getValues(stringstream& ss) {
    for (auto i = 0U; i < stream_.getContents().size(); ++i) {
        auto content = stream_.getContents()[i];
        ss << content;
        if (i != stream_.getContents().size() - 1)
            ss << ",";
    }
    return true;
}

bool DBDefine::exist(const char* key, Basic::AnyValue value) {
    return this->execter->pull(key, value, this);
}

