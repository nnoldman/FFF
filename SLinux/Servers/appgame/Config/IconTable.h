#ifndef IconTable_h__
#define IconTable_h__
/*
@author: Administrator
@time:2017/11/6 14:42:34
*/

#include "DataLoader.h"

struct IconTableRecord:public RecordBase
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
			auto& column = columns[i];
			int* indices = getColumnIndices();
			if (column == "ID")
				indices[0] = i + 1;
			else if (column == "TextureID")
				indices[1] = i + 1;
			else if (column == "Explain")
				indices[2] = i + 1;
			else if (column == "PX")
				indices[3] = i + 1;
			else if (column == "PY")
				indices[4] = i + 1;
			else if (column == "Width")
				indices[5] = i + 1;
			else if (column == "Height")
				indices[6] = i + 1;
			else if (column == "FrameCount")
				indices[7] = i + 1;
			else if (column == "FPL")
				indices[8] = i + 1;
		}
	}
	void from(const std::vector<string>& values)
	{
	int* indices = getColumnIndices();
		if (indices[0] > 0)
			Basic::StringHelper::setValue(values[indices[0] - 1].c_str(), &ID);
		if (indices[1] > 0)
			Basic::StringHelper::setValue(values[indices[1] - 1].c_str(), &TextureID);
		if (indices[2] > 0)
			Basic::StringHelper::setValue(values[indices[2] - 1].c_str(), &Explain);
		if (indices[3] > 0)
			Basic::StringHelper::setValue(values[indices[3] - 1].c_str(), &PX);
		if (indices[4] > 0)
			Basic::StringHelper::setValue(values[indices[4] - 1].c_str(), &PY);
		if (indices[5] > 0)
			Basic::StringHelper::setValue(values[indices[5] - 1].c_str(), &Width);
		if (indices[6] > 0)
			Basic::StringHelper::setValue(values[indices[6] - 1].c_str(), &Height);
		if (indices[7] > 0)
			Basic::StringHelper::setValue(values[indices[7] - 1].c_str(), &FrameCount);
		if (indices[8] > 0)
			Basic::StringHelper::setValue(values[indices[8] - 1].c_str(), &FPL);
	}
};

class IconTable :public DataLoader<IconTableRecord>
{
public:
    static IconTable* getInstance()
    {
        static IconTable t;
        return &t;
    }
    virtual const char* fileName() override
    {
        return "IconTable.txt";
    }
#include "IconTable.inl"
};

#endif // {IconTable}_h__
