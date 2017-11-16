#include "stdafx.h"
#include "DBObject.h"
#include "DBDefine.h"

DBObject::DBObject()
    :dbInterface_(nullptr)
    , netInterface_(nullptr) {
    printf("DBObject():%x",this);
}

DBObject::~DBObject() {
    dSafeDelete(dbInterface_);
    netInterface_ = nullptr;
    printf("~DBObject():%x", this);
}
bool DBObject::initialize() {
    this->createDefine();
    return true;
}

void DBObject::setGlobalID(int globalID) {
    dbInterface_->id = globalID;
    globalID_ = globalID;
}

void DBObject::syncToClient() {
}

