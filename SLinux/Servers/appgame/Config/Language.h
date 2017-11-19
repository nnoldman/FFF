#ifndef Language_h__
#define Language_h__
/*
@author: nn
@time:2017/11/2 12:15:41
*/


struct LanguageRecord: public RecordBase {
  public:
    int id;
    string text;

  public:
    static int* getColumnIndices() {
        static int columnIndices[2] = {0, 0};
        return columnIndices;
    }
    static void initColumnIndices(const std::vector<string>& columns) {
        for (int i = 0; i < columns.size(); ++i) {
            if (columns[i] == "id")
                getColumnIndices()[0] = i + 1;
            else if (columns[i] == "text")
                getColumnIndices()[1] = i + 1;
        }
    }
    void from(const std::vector<string>& values) {
        if (getColumnIndices()[0] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[0] - 1].c_str(), &id);
        if (getColumnIndices()[1] > 0)
            Basic::StringHelper::setValue(values[getColumnIndices()[1] - 1].c_str(), &text);
    }
};

class Language : public DataLoader<LanguageRecord> {
  public:
    static Language* getInstance() {
        static Language t;
        return &t;
    }
    virtual const char* fileName() override {
        return "Language.txt";
    }
    const string& getContent(int id) {
        auto record = get(id);
        if (record)
            return record->text;
        static string empty;
        return empty;
    }
#include "Language.inl"
};

#endif // {Language}_h__
