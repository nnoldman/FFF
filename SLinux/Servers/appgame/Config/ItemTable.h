#ifndef ItemTable_h__
#define ItemTable_h__
/*
@author: Administrator
@time:2017/11/6 16:24:22
*/

struct ItemTableRecord:public RecordBase {
  public:
    int ID;
    string Name;
    int Level;
    int Type;
    int MaxNum;
    int Quality;
    int AutoSell;
    int Use;
    int BuyPrice;
    int GoldPrice;
    int GongDe;
    int Recovery;
    string Desc;
    string Legend;
    int Icon;
    int MinAttack;
    int MaxAttack;
    int MinDefence;
    int MaxDefence;
    int MinWAttack;
    int MaxWAttack;
    int MinMAttack;
    int MaxMAttack;
    int MinGAttack;
    int MaxGAttack;
    int MinPAttack;
    int MaxPAttack;
    int MinDodge;
    int MaxDodge;
    int MinBang;
    int MaxBang;
    int MinASpeed;
    int MaxASpeed;
    int MinMSpeed;
    int MaxMSpeed;
    int MinAntiMine;
    int MaxAntiMine;
    int Body;
    int Soul;
    int UseLimit;

  public:
    static int* getColumnIndices() {
        static int columnIndices[40]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        return columnIndices;
    }
    static void initColumnIndices(const std::vector<string>& columns) {
        for (int i = 0; i < columns.size(); ++i) {
            auto& column = columns[i];
            int* indices = getColumnIndices();
            if (column == "ID")
                indices[0] = i + 1;
            else if (column == "Name")
                indices[1] = i + 1;
            else if (column == "Level")
                indices[2] = i + 1;
            else if (column == "Type")
                indices[3] = i + 1;
            else if (column == "MaxNum")
                indices[4] = i + 1;
            else if (column == "Quality")
                indices[5] = i + 1;
            else if (column == "AutoSell")
                indices[6] = i + 1;
            else if (column == "Use")
                indices[7] = i + 1;
            else if (column == "BuyPrice")
                indices[8] = i + 1;
            else if (column == "GoldPrice")
                indices[9] = i + 1;
            else if (column == "GongDe")
                indices[10] = i + 1;
            else if (column == "Recovery")
                indices[11] = i + 1;
            else if (column == "Desc")
                indices[12] = i + 1;
            else if (column == "Legend")
                indices[13] = i + 1;
            else if (column == "Icon")
                indices[14] = i + 1;
            else if (column == "MinAttack")
                indices[15] = i + 1;
            else if (column == "MaxAttack")
                indices[16] = i + 1;
            else if (column == "MinDefence")
                indices[17] = i + 1;
            else if (column == "MaxDefence")
                indices[18] = i + 1;
            else if (column == "MinWAttack")
                indices[19] = i + 1;
            else if (column == "MaxWAttack")
                indices[20] = i + 1;
            else if (column == "MinMAttack")
                indices[21] = i + 1;
            else if (column == "MaxMAttack")
                indices[22] = i + 1;
            else if (column == "MinGAttack")
                indices[23] = i + 1;
            else if (column == "MaxGAttack")
                indices[24] = i + 1;
            else if (column == "MinPAttack")
                indices[25] = i + 1;
            else if (column == "MaxPAttack")
                indices[26] = i + 1;
            else if (column == "MinDodge")
                indices[27] = i + 1;
            else if (column == "MaxDodge")
                indices[28] = i + 1;
            else if (column == "MinBang")
                indices[29] = i + 1;
            else if (column == "MaxBang")
                indices[30] = i + 1;
            else if (column == "MinASpeed")
                indices[31] = i + 1;
            else if (column == "MaxASpeed")
                indices[32] = i + 1;
            else if (column == "MinMSpeed")
                indices[33] = i + 1;
            else if (column == "MaxMSpeed")
                indices[34] = i + 1;
            else if (column == "MinAntiMine")
                indices[35] = i + 1;
            else if (column == "MaxAntiMine")
                indices[36] = i + 1;
            else if (column == "Body")
                indices[37] = i + 1;
            else if (column == "Soul")
                indices[38] = i + 1;
            else if (column == "UseLimit")
                indices[39] = i + 1;
        }
    }
    void from(const std::vector<string>& values) {
        int* indices = getColumnIndices();
        if (indices[0] > 0)
            Basic::StringHelper::setValue(values[indices[0] - 1].c_str(), &ID);
        if (indices[1] > 0)
            Basic::StringHelper::setValue(values[indices[1] - 1].c_str(), &Name);
        if (indices[2] > 0)
            Basic::StringHelper::setValue(values[indices[2] - 1].c_str(), &Level);
        if (indices[3] > 0)
            Basic::StringHelper::setValue(values[indices[3] - 1].c_str(), &Type);
        if (indices[4] > 0)
            Basic::StringHelper::setValue(values[indices[4] - 1].c_str(), &MaxNum);
        if (indices[5] > 0)
            Basic::StringHelper::setValue(values[indices[5] - 1].c_str(), &Quality);
        if (indices[6] > 0)
            Basic::StringHelper::setValue(values[indices[6] - 1].c_str(), &AutoSell);
        if (indices[7] > 0)
            Basic::StringHelper::setValue(values[indices[7] - 1].c_str(), &Use);
        if (indices[8] > 0)
            Basic::StringHelper::setValue(values[indices[8] - 1].c_str(), &BuyPrice);
        if (indices[9] > 0)
            Basic::StringHelper::setValue(values[indices[9] - 1].c_str(), &GoldPrice);
        if (indices[10] > 0)
            Basic::StringHelper::setValue(values[indices[10] - 1].c_str(), &GongDe);
        if (indices[11] > 0)
            Basic::StringHelper::setValue(values[indices[11] - 1].c_str(), &Recovery);
        if (indices[12] > 0)
            Basic::StringHelper::setValue(values[indices[12] - 1].c_str(), &Desc);
        if (indices[13] > 0)
            Basic::StringHelper::setValue(values[indices[13] - 1].c_str(), &Legend);
        if (indices[14] > 0)
            Basic::StringHelper::setValue(values[indices[14] - 1].c_str(), &Icon);
        if (indices[15] > 0)
            Basic::StringHelper::setValue(values[indices[15] - 1].c_str(), &MinAttack);
        if (indices[16] > 0)
            Basic::StringHelper::setValue(values[indices[16] - 1].c_str(), &MaxAttack);
        if (indices[17] > 0)
            Basic::StringHelper::setValue(values[indices[17] - 1].c_str(), &MinDefence);
        if (indices[18] > 0)
            Basic::StringHelper::setValue(values[indices[18] - 1].c_str(), &MaxDefence);
        if (indices[19] > 0)
            Basic::StringHelper::setValue(values[indices[19] - 1].c_str(), &MinWAttack);
        if (indices[20] > 0)
            Basic::StringHelper::setValue(values[indices[20] - 1].c_str(), &MaxWAttack);
        if (indices[21] > 0)
            Basic::StringHelper::setValue(values[indices[21] - 1].c_str(), &MinMAttack);
        if (indices[22] > 0)
            Basic::StringHelper::setValue(values[indices[22] - 1].c_str(), &MaxMAttack);
        if (indices[23] > 0)
            Basic::StringHelper::setValue(values[indices[23] - 1].c_str(), &MinGAttack);
        if (indices[24] > 0)
            Basic::StringHelper::setValue(values[indices[24] - 1].c_str(), &MaxGAttack);
        if (indices[25] > 0)
            Basic::StringHelper::setValue(values[indices[25] - 1].c_str(), &MinPAttack);
        if (indices[26] > 0)
            Basic::StringHelper::setValue(values[indices[26] - 1].c_str(), &MaxPAttack);
        if (indices[27] > 0)
            Basic::StringHelper::setValue(values[indices[27] - 1].c_str(), &MinDodge);
        if (indices[28] > 0)
            Basic::StringHelper::setValue(values[indices[28] - 1].c_str(), &MaxDodge);
        if (indices[29] > 0)
            Basic::StringHelper::setValue(values[indices[29] - 1].c_str(), &MinBang);
        if (indices[30] > 0)
            Basic::StringHelper::setValue(values[indices[30] - 1].c_str(), &MaxBang);
        if (indices[31] > 0)
            Basic::StringHelper::setValue(values[indices[31] - 1].c_str(), &MinASpeed);
        if (indices[32] > 0)
            Basic::StringHelper::setValue(values[indices[32] - 1].c_str(), &MaxASpeed);
        if (indices[33] > 0)
            Basic::StringHelper::setValue(values[indices[33] - 1].c_str(), &MinMSpeed);
        if (indices[34] > 0)
            Basic::StringHelper::setValue(values[indices[34] - 1].c_str(), &MaxMSpeed);
        if (indices[35] > 0)
            Basic::StringHelper::setValue(values[indices[35] - 1].c_str(), &MinAntiMine);
        if (indices[36] > 0)
            Basic::StringHelper::setValue(values[indices[36] - 1].c_str(), &MaxAntiMine);
        if (indices[37] > 0)
            Basic::StringHelper::setValue(values[indices[37] - 1].c_str(), &Body);
        if (indices[38] > 0)
            Basic::StringHelper::setValue(values[indices[38] - 1].c_str(), &Soul);
        if (indices[39] > 0)
            Basic::StringHelper::setValue(values[indices[39] - 1].c_str(), &UseLimit);
    }
};

class ItemTable :public DataLoader<ItemTableRecord> {
  public:
    static ItemTable* getInstance() {
        static ItemTable t;
        return &t;
    }
    virtual const char* fileName() override {
        return "ItemTable.txt";
    }
#include "ItemTable.inl"
};

#endif // {ItemTable}_h__
