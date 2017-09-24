#ifndef TimeTable_h__
#define TimeTable_h__
/*
@author nn oldman
*/

#include "DataLoader.h"

struct TimeTableRecord:public RecordBase
{
public:
int level;
string period;
string era;
int start;
string intro;

public:
    static int* getColumnIndices()
{
    static int columnIndices[{0}]={0,0,0,0,0};
        return columnIndices;
}
    static void initColumnIndices(const std::vector<string>& columns)
{
    for (int i = 0; i < columns.size(); ++i)    {
if (columns[0] == "level")
getColumnIndices()[0] = i + 1;
else if (columns[1] == "period")
getColumnIndices()[1] = i + 1;
else if (columns[2] == "era")
getColumnIndices()[2] = i + 1;
else if (columns[3] == "start")
getColumnIndices()[3] = i + 1;
else if (columns[4] == "intro")
getColumnIndices()[4] = i + 1;
    }
}
    void from(const std::vector<string>& values)
{
   if (getColumnIndices()[0] > 0)
       Basic::StringHelper::setValue(values[getColumnIndices()[0] - 1].c_str(), &level);
else    if (getColumnIndices()[1] > 0)
       Basic::StringHelper::setValue(values[getColumnIndices()[1] - 1].c_str(), &period);
else    if (getColumnIndices()[2] > 0)
       Basic::StringHelper::setValue(values[getColumnIndices()[2] - 1].c_str(), &era);
else    if (getColumnIndices()[3] > 0)
       Basic::StringHelper::setValue(values[getColumnIndices()[3] - 1].c_str(), &start);
else    if (getColumnIndices()[4] > 0)
       Basic::StringHelper::setValue(values[getColumnIndices()[4] - 1].c_str(), &intro);
    }
}
}

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

#endif // {TimeTable}_h__

