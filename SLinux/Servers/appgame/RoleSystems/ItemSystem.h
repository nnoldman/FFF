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
    ���ٵ���
    */
    void destroy(int dbID, GameDefine::ItemDeleteReason reason);

    /*
    ˢ�µ�������
    */
    void refresh(int dbID, int count, GameDefine::ItemRefreshReason reason = GameDefine::ItemRefreshReason_None);

    /*
    ���۵���
    */
    bool sell(int dbID, GameDefine::ItemSellSource source = GameDefine::ItemSellSource_Invalid);

    /*
    ʹ�õ���
    */
    bool useItem(int dbID, int num = 1);

    /*
    �ƶ�����
    */
    bool moveItem(int dbID, GameDefine::ItemLocation locationSrc, int xSrc, GameDefine::ItemLocation locationDst, int xDst);
protected:
    virtual void onTimer(Basic::Timer* timer)override;
    virtual void onTimerEnd(Basic::Timer* timer)override;
    void syncToClient();
    void pullFromDB();
    void testSystem();
    /*
    ���ɵ���
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

