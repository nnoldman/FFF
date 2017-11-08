#ifndef Icon_h__
#define Icon_h__
/*
@author: nn
@time:2017/11/4 19:49:00
*/

#include "DataLoader.h"

struct IconRecord:public RecordBase
{
public:
	int ID;
	int TextureID;
	string Explain;
	int PX;
	int PY;
	int Width;
	int Height;
	int FrameCount;
	int FPL;

public:
	static int* getColumnIndices()
	{
		static int columnIndices[9]={0,0,0,0,0,0,0,0,0};
		return columnIndices;
	}
	static void initColumnIndices(const std::vector<string>& columns)
	{
		for (int i = 0; i < columns.size(); ++i)
		{
			if (columns[i] == "ID")
				getColumnIndices()[0] = i + 1;
			else if (columns[i] == "TextureID")
				getColumnIndices()[1] = i + 1;
			else if (columns[i] == "Explain")
				getColumnIndices()[2] = i + 1;
			else if (columns[i] == "PX")
				getColumnIndices()[3] = i + 1;
			else if (columns[i] == "PY")
				getColumnIndices()[4] = i + 1;
			else if (columns[i] == "Width")
				getColumnIndices()[5] = i + 1;
			else if (columns[i] == "Height")
				getColumnIndices()[6] = i + 1;
			else if (columns[i] == "FrameCount")
				getColumnIndices()[7] = i + 1;
			else if (columns[i] == "FPL")
				getColumnIndices()[8] = i + 1;
		}
	}
	void from(const std::vector<string>& values)
	{
		if (getColumnIndices()[0] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[0] - 1].c_str(), &ID);
		if (getColumnIndices()[1] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[1] - 1].c_str(), &TextureID);
		if (getColumnIndices()[2] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[2] - 1].c_str(), &Explain);
		if (getColumnIndices()[3] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[3] - 1].c_str(), &PX);
		if (getColumnIndices()[4] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[4] - 1].c_str(), &PY);
		if (getColumnIndices()[5] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[5] - 1].c_str(), &Width);
		if (getColumnIndices()[6] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[6] - 1].c_str(), &Height);
		if (getColumnIndices()[7] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[7] - 1].c_str(), &FrameCount);
		if (getColumnIndices()[8] > 0)
			Basic::StringHelper::setValue(values[getColumnIndices()[8] - 1].c_str(), &FPL);
	}
};

class Icon :public DataLoader<IconRecord>
{
public:
    static Icon* getInstance()
    {
        static Icon t;
        return &t;
    }
    virtual const char* fileName() override
    {
        return "Icon.txt";
    }
#include "Icon.inl"
};

#endif // {Icon}_h__
