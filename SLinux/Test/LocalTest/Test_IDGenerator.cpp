#include "stdafx.h"
#include "Installer.h"
#include "IDGenerator.h"
#include "Random.h"

Function(Test_IDGenerator)
{
    Basic::IDGenerator generator;
    for(int i = 0; i < 1000; ++i)
    {
        auto ret = generator.require();
        //std::cout << "IT:" << Basic::Random::getInstance().randI(1, 30) << std::endl;
    }
    auto& set = generator.set();
    for (auto it : set)
    {
        //std::cout << "IT:" << it << std::endl;
    }
}