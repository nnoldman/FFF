virtual int TimeTable::getKey(RecordBase* base) override
{
    auto record=(TimeTableRecord*)base;
    return record->level;
}

