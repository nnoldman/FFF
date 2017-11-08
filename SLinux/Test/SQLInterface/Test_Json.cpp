#include "stdafx.h"
#include "Test_Json.h"
#include "Objects.h"
#include "JsonWriter.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonReader.h"
#include <iostream>
Test_Json::Test_Json()
{
    this->test_write();
}


Test_Json::~Test_Json()
{
}

void Test_Json::test_write()
{
    {
        Objects::Role role;
        role.id = 5;
        role.name = "10";
        for (int i = 0; i < 4; ++i)
        {
            role.equips[i].id = i + 1;
            role.equips[i].name = "ff";
        }
        role.equips2.push_back({ 1, "5", '3' });
        Serializer::JsonWriter writer;
        writer.write(role);
        //std::fstream fs;
        //fs.open("test.json", ios::out);
        //if (fs)
        //{
        //    fs << writer.text();
        //    fs.close();
        //}
        Objects::Role role1;
        Serializer::JsonReader reader;
        reader.fromText(writer.text(), role1);
        assert(role1.id == role.id);
        assert(role1.name == role.name);
        assert(role1.equips2[0].id == 1);
        assert(role1.equips2[0].name == "5");
        assert(role1.equips2[0].quality == '3');
        std::cout << typeid(role.equips).name() << std::endl;
        std::cout << typeid(role.equips2).name() << std::endl;
    }
}