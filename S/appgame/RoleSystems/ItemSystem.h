#pragma once
#include "..\ItemDefine.h"
class ItemSystem
{
public:
    ItemSystem();
    ~ItemSystem();

public:

    /*
    ���ٵ���
    */
    void destroy(int dbID, GameDefine::ItemDeleteReason reason);

    /*
    ���ɵ���
    */
    ItemDefine* create(int itemID,GameDefine::ItemLocation location,int x);

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
};

