#pragma once
#include "SystemBase.h"
#include "TableDefine/ItemDefine.h"
class ItemSystem : public SystemBase
{
public:
    ItemSystem();
    ~ItemSystem();
    virtual void initialize(Role* role) override;
    virtual void archieve() override;
public:

    /*
    销毁道具
    */
    void destroy(int dbID, GameDefine::ItemDeleteReason reason);

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
protected:
    virtual void onTimer(Basic::Timer* timer)override;
    virtual void onTimerEnd(Basic::Timer* timer)override;
    void syncToClient();
    void pullFromDB();
    void testSystem();
    /*
    生成道具
    */
    ItemDefine* create(int itemID, int num, int cell, int position );

    int getFirstEmptySlot(GameDefine::ObjectCellType cell);
    bool empty(GameDefine::ObjectCellType cell);
    int getStartIndex(GameDefine::ObjectCellType cell);
    int getIndex(GameDefine::ObjectCellType cell, int position);
private:
    std::weak_ptr<Basic::Timer> testTimer_;
    ItemDefine* objects_[ItemDefine::ObjectsCapacity];
    Basic::IDGenerator idGenerator_;
    static int sCellCapicity[];
};

