#ifndef TimeTable_h__
#define TimeTable_h__

/*
@author nn oldman
工具生成，请勿修改！
*/

#include "DataLoader.h"

struct TimeTableRecord :
    public RecordBase
{
public:
    int level;
    string period;
    string era;
    s64 start;
    string intro;
public:
    static int* getColumnIndices()
    {
        static int columnIndices[5] = { 0,0,0,0,0 };
        return columnIndices;
    }

    static void initColumnIndices(const std::vector<string>& columns)
    {
        for (int i = 0; i < columns.size(); ++i)
        {
            if (columns[i] == "level")
                getColumnIndices()[0] = i + 1;
            else if (columns[i] == "period")
                getColumnIndices()[1] = i + 1;
            else if (columns[i] == "era")
                getColumnIndices()[2] = i + 1;
            else if (columns[i] == "start")
                getColumnIndices()[3] = i + 1;
            else if (columns[i] == "intro")
                getColumnIndices()[4] = i + 1;
        }
    }

    void from(const std::vector<string>& values)
    {
        if (getColumnIndices()[0] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[0] - 1].c_str(), &level);
        if (getColumnIndices()[1] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[1] - 1].c_str(), &period);
        if (getColumnIndices()[2] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[2] - 1].c_str(), &era);
        if (getColumnIndices()[3] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[3] - 1].c_str(), &start);
        if (getColumnIndices()[4] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[4] - 1].c_str(), &intro);
    }
};

class TimeTable :public DataLoader<TimeTableRecord>
{
public:
    static TimeTable* getInstance()
    {
        static TimeTable t;
        return &t;
    }
    virtual const char* fileName() override
    {
        return "TimeTable.txt";
    }
#include "TimeTable.inl"
};

#endif // TimeTable_h__
