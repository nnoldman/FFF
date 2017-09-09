#include "stdafx.h"
#include "Account.h"
#include "App.h"
#include "Bundle.h"
#include "GlobalAccountDefine.h"
Account::Account()
{
}


Account::~Account()
{
    printf("~Account()\n");
}

void Account::onEnterGate()
{
    //this->call("enterWorld");
}

void Account::onRoleRqEnterWorld(int globalID)
{
}

void Account::enterWorld()
{
}



void Account::createDefine()
{
    this->dbInterface_ = new GlobalAccountDefine();
}



bool Account::initialize()
{
    if (!__super::initialize())
        return false;
    return true;
}
