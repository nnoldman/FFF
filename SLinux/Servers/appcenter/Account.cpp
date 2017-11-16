#include "stdafx.h"
#include "Account.h"
#include "App.h"
#include "Bundle.h"
#include "GlobalAccountDefine.h"
Account::Account() {
}


Account::~Account() {
    printf("~Account()\n");
}

void Account::onEnterGate() {
    //this->call("enterWorld");
}

void Account::onRoleRqEnterWorld(int globalID) {
}

void Account::enterWorld() {
}



void Account::createDefine() {
    this->dbInterface_ = App::DataBase.createDefine<GlobalAccountDefine>();
}



bool Account::initialize() {
    if (!DBObject::initialize())
        return false;
    return true;
}
