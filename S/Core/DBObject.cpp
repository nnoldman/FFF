#include "stdafx.h"
#include "DBObject.h"
#include "DBDefine.h"


DBObject::DBObject()
    : netInterface_(nullptr)
    , dbInterface_(nullptr)
{
}

DBObject::~DBObject()
{
    dSafeDelete(dbInterface_);
    if (netInterface_)
    {
        netInterface_->disconnect();
        netInterface_ = nullptr;
    }
}
bool DBObject::initialize()
{
    this->createDefine();
    return true;
}

void DBObject::setGlobalID(int globalID)
{
    globalID_ = globalID;
    this->dbInterface_->key();
}

void DBObject::syncToClient()
{

}


//bool DBObject::pull(Value keyValue)
//{
//    return this->dbInterface_->pull(keyValue);
//}
//
//
//bool DBObject::commit(Value keyValue)
//{
//    return this->dbInterface_->commit(keyValue);
//}

