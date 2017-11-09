#pragma once
namespace ServerDefine
{
    class Capcity
    {
    public:
        static const int BagLimit = 180;
    };

    enum SystemType
    {
        SystemType_Level,
        SystemType_Item,
        SystemType_Task,
        SystemType_Chat,
        SystemType_Count,
    };
}

