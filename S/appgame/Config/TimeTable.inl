virtual int TimeTable::getKey(RecordBase* base) override
{
    return ((TimeTableRecord*)base)->level;
}

