virtual int Icon::getKey(RecordBase* base) override
{
    auto record = (IconRecord*)base;
    return record->ID;
}

