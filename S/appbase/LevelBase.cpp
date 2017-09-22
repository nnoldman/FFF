#include "stdafx.h"
#include "LevelBase.h"

int LevelBase::getKey()
{
    return level;
}

bool LevelBase::parse(string line)
{
    return true;
}

const char* LevelBases::fileName()
{
    return "LevelBase.txt";
}
