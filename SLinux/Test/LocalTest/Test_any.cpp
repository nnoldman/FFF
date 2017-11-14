#include "stdafx.h"
#include "Installer.h"
#include "..\Basic\AnyValue.h"
using namespace Basic;

Function(Test_Construct)
{
    AnyValue var_int5(5);
    AssertTrue(var_int5.isNumber());
    AssertTrue(var_int5.get<int>() == 5);
    AnyValue var_int3 = 3;
    AssertTrue(var_int3.get<int>() == 3);
    var_int3 = var_int5;
    AssertTrue(var_int3.get<int>() == 5);
    AssertTrue(var_int5.get<int>() == 5);
    auto var = var_int5.get<string>();
    AnyValue var_string("515");
    AssertTrue(var_string.isString());
    AssertTrue(var_string.get<string>() == "515");
}