#include "appcenter.h"
#include "Account.h"
#include "App.h"
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
    this->dbInterface_ = DBService::get()->createDefine<GlobalAccountDefine>();
}



bool Account::initialize() {
    if (!GameEntity::initialize())
        return false;
    return true;
}
