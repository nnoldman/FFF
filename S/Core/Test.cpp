#include "stdafx.h"
#include "Test.h"
#include "App.h"
Test gTest;

Test::Test() {
}


Test::~Test() {
}

void Test::DoWork() {
    MonoEngine& gMono = App::Script;
    {
        MonoObject* client = gMono.newObject("Scripts", "Test");
        ScriptArgs arg;

        gMono.invoke("Scripts", "Test", "testVoid", client, nullptr);

        arg << "stringparam"
            << 15;
        gMono.invoke("Scripts", "Test", "testParam", client, arg.pointer());
    }
    {
        ScriptObject* sp = new ScriptObject("DataInitializer", "DataBase");
        sp->init();
        int count = 0;
        sp->getField("count", count);
        assert(count == 6);
        delete sp;
    }
    {
        Account* account = new Account();
        account->init();
        DBInterface* dbobject = account->getDBInterface();
        dbobject->setField("user", "liming");

        string suser;
        dbobject->getField("user", suser);
        assert(suser == "liming");

        int initn = 0;
        dbobject->getField("test", initn);
        assert(initn == 5);
        dbobject->setField("test", 8);
        dbobject->getField("test", initn);
        assert(initn == 8);
        delete account;
    }
}
