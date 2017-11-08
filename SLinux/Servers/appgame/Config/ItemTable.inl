virtual int getKey(RecordBase* base) override
{
    auto record = (ItemTableRecord*)base;
    return record->ID;
}

