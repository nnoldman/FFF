// TestMysql.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MySqlExecuter.h"
#include "TableDefine/GameUserDefine.h"
#include "TableDefine/ItemDefine.h"
#include "DataBase.h"


int main() {
    {
        DBConfig config;
        //config.host = "43.248.102.164";
        config.user = "root";
        config.password = "ni2handan";
        config.port = 3306;
        config.dbName = "ff";
        //

        const vector<const DBTableDefine*> defines = {
            &GameUserDefine::GetDefine()
            ,&ItemDefine::GetDefine()
        };

        DataBase db;
        assert(db.initialize(config));
        db.checkDefines(defines);

        {
            for (int i = 0; i < 500; ++i) {
                GameUserDefine* def = db.createDefine<GameUserDefine>();
                def->id = i;
                def->role = i;
                assert(def->commitByKey1());
                delete def;
            }
        }
        {
            for (int i = 0; i < 200; ++i) {
                auto* def = db.createDefine<ItemDefine>();
                def->id = 1;
                def->cell = 5;
                def->itemID = i + 1;
                def->borntime = "2017-08-10 11:11:11";
                def->dbID = i + 1;
                assert(def->commitByKey1Key2(def->dbID));
                delete def;
            }

            for (int i = 0; i < 200; ++i) {
                auto* def = db.createDefine<ItemDefine>();
                def->id = 1;
                def->cell = 5;

                def->dbID = i + 1;

                assert(def->pullByKey1Key2(def->dbID));
                assert(def->itemID = i + 1);
                delete def;
            }
        }
    }
    return 0;
}

