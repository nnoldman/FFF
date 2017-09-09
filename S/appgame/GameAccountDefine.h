#pragma once
#include "DBDefine.h"
class GameAccountDefine: DBDefine {
  public:
    virtual const char* table() override {
        tableName.c_str();
    }

    virtual const char* key() override {
        throw std::exception("The method or operation is not implemented.");
    }

    virtual void deserialize() override {
    }

    virtual void serialize() override {
        throw std::exception("The method or operation is not implemented.");
    }

};

