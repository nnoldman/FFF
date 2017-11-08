#include "stdafx.h"
#include "DBDefine.h"
#include "App.h"
#include "DataBase.h"
#include "Value.h"

const char* DBDefine::key2()
{
    return nullptr;
}

void DBDefine::deserialize()
{
    this->stream().reposition();
    this->deserializeMe();
}

void DBDefine::serialize()
{
    this->stream().clear();
    this->serializeMe();
}


void DBDefine::set(vector<string>& values)
{
    stream_.set(values);
}

bool DBDefine::pull(AnyObject keyvalue)
{
    return App::DataBase.pull(keyvalue, this);
}

bool DBDefine::commitByKey1()
{
    return App::DataBase.commitByKey1(this);
}

bool DBDefine::commitByKey1Key2(AnyObject key2value)
{
    return App::DataBase.commitByKey1Key2(this, key2value);
}

bool DBDefine::insertByKey1()
{
}

bool DBDefine::insertByKey1Key2(AnyObject key2value)
{
}

//delete from global_account where user = '123';
bool DBDefine::insertAndQuery(AnyObject keyvalue)
{
    if (App::DataBase.insert(this))
        return pull(keyvalue);
    return false;
}

bool DBDefine::insertAndQuery(const char* key, AnyObject keyvalue)
{
    if (App::DataBase.insert(this))
        return App::DataBase.pull(key, keyvalue, this);
    return false;
}

bool DBDefine::getValues(stringstream& ss)
{
    for (auto i = 0; i < stream_.getContents().size(); ++i)
    {
        auto content = stream_.getContents()[i];
        ss << content;
        if (i != stream_.getContents().size() - 1)
            ss << ",";
    }
    return true;
}

bool DBDefine::exist(const char* key, AnyObject value)
{
    return App::DataBase.pull(key, value, this);
}

