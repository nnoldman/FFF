#include "stdafx.h"
#include "Installer.h"
#include <algorithm>

Function(Test_Lambda)
{
    vector<string> array = {"FD", "xy", "zf", "abx"};
    std::for_each(array.begin(), array.end(), [](auto it)
    {
        std::cout << it << std::endl;
    });
    auto ret = std::find_if(array.begin(), array.end(), [](auto it)
    {
        return it[0] == 'z';
    });
    assert(*ret == "zf");
}
