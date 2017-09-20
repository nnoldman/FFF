#pragma once
#include "..\ItemDefine.h"
class ItemSystem
{
public:
    ItemSystem();
    ~ItemSystem();

public:

    /*
    销毁道具
    */
    void destroy(int dbID, GameDefine::ItemDeleteReason reason);

    /*
    生成道具
    */
    ItemDefine* create(int itemID,GameDefine::ItemLocation location,int x);

    /*
    刷新道具数量
    */
    void refresh(int dbID, int count, GameDefine::ItemRefreshReason reason = GameDefine::ItemRefreshReason_None);

    /*
    出售道具
    */
    bool sell(int dbID, GameDefine::ItemSellSource source = GameDefine::ItemSellSource_Invalid);

    /*
    使用道具
    */
    bool useItem(int dbID, int num = 1);

    /*
    移动道具
    */
    bool moveItem(int dbID, GameDefine::ItemLocation locationSrc, int xSrc, GameDefine::ItemLocation locationDst, int xDst);
};

