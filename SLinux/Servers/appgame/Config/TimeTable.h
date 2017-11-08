#ifndef TimeTable_h__
#define TimeTable_h__
/*
@author: Administrator
@time:2017/11/6 14:43:32
*/

#include "DataLoader.h"

struct TimeTableRecord:public RecordBase
{
public:
	int level;
	string period;
	string era;
	s64 start;
	int realtime;
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
			auto& column = columns[i];
			int* indices = getColumnIndices();
			if (column == "level")
				indices[0] = i + 1;
			else if (column == "period")
				indices[1] = i + 1;
			else if (column == "era")
				indices[2] = i + 1;
			else if (column == "start")
				indices[3] = i + 1;
			else if (column == "realtime")
				indices[4] = i + 1;
			else if (column == "intro")
				indices[5] = i + 1;
		}
	}
	void from(const std::vector<string>& values)
	{
	int* indices = getColumnIndices();
		if (indices[0] > 0)
			Basic::StringHelper::setValue(values[indices[0] - 1].c_str(), &level);
		if (indices[1] > 0)
			Basic::StringHelper::setValue(values[indices[1] - 1].c_str(), &period);
		if (indices[2] > 0)
			Basic::StringHelper::setValue(values[indices[2] - 1].c_str(), &era);
		if (indices[3] > 0)
			Basic::StringHelper::setValue(values[indices[3] - 1].c_str(), &start);
		if (indices[4] > 0)
			Basic::StringHelper::setValue(values[indices[4] - 1].c_str(), &realtime);
		if (indices[5] > 0)
			Basic::StringHelper::setValue(values[indices[5] - 1].c_str(), &intro);
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
