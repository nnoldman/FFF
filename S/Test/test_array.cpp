#include "stdafx.h"
#include "test_array.h"
#include <array>
#include <iostream>


test_array::test_array()
{
    std::array<string, 5> arr;
    arr[0] = "123";
    arr[1] = "1234";
    arr[2] = "12345";
    arr[3] = "123456";
    arr[4] = "1234567";
    assert(arr.size() == 5);
    assert(arr.front() == "123");
    assert(arr.back() == "1234567");

    for (auto iter : arr)
    {
        std::cout << iter << std::endl;
    }
}


test_array::~test_array()
{
}
