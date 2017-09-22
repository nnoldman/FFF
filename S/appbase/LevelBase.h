#pragma once
#include "RecordBase.h"
#include "DataLoader.h"
struct LevelBase :
    public RecordBase
{
    int level;
    string period;
    string era;
    int start;
    string intro;

    virtual int getKey() override;

    bool parse(string line);


};

class LevelBases :DataLoader<LevelBase>
{
public:
    virtual const char* fileName() override;
};

