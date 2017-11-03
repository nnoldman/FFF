virtual int getKey(RecordBase* base) override
{
    auto record = (LanguageRecord*)base;
    return record->id;
}

