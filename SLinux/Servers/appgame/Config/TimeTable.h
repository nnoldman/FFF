#ifndef TimeTable_h__
#define TimeTable_h__
/*
@author: nn
@time:2017/10/23 14:56:35
*/

#include "DataLoader.h"

struct TimeTableRecord:public RecordBase
{
public:
	int level;
	string period;
	string era;
	s64 start;
	int speed;
	string intro;

public:
	static int* getColumnIndices()
	{
		static int columnIndices[6]={0,0,0,0,0,0};
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
			else if (columns[i] == "speed")
				getColumnIndices()[4] = i + 1;
			else if (columns[i] == "intro")
				getColumnIndices()[5] = i + 1;
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
			Basic::StringHelper::setValue(values[getColumnIndices()[4] - 1].c_str(), &speed);
		if (getColumnIndices()[5] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[5] - 1].c_str(), &intro);
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

#endif // {TimeTable}_h__
