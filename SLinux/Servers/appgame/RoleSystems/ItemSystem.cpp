#include "../stdafx.h"
#include "ItemSystem.h"
#include "TableDefine/GameRoleDefine.h"
#include "TableDefine/ItemDefine.h"
#include "Config/ItemTable.h"
int ItemSystem::sCellCapicity[] = {
    GameDefine::Capcity::Bag
    , GameDefine::Capcity::Equip
};

ItemSystem::ItemSystem() {
    dMemoryZeroArray(this->objects_);
}
ItemSystem::~ItemSystem() {
    if (!this->testTimer_.expired())
        this->testTimer_.lock()->cancel();
    dSafeDeleteArray(this->objects_);
}


void ItemSystem::initialize(Role* role) {
    SystemBase::initialize(role);
    this->pullFromDB();
    this->syncToClient();
    this->testSystem();
}

void ItemSystem::archieve() {
    for (auto it : this->objects_) {
        if (it && it->dbID > 0)
            it->commitByKey1Key2(it->dbID);
    }
}

void ItemSystem::destroy(int dbID, GameDefine::ItemDeleteReason reason) {
}

ItemDefine* ItemSystem::create(int itemID, int num, int cell, int position) {
    auto index = getIndex((GameDefine::ObjectCellType)cell, position);
    if (index == -1)
        return nullptr;
    assert(this->objects_[index] == nullptr);
    auto ret = App::DataBase.createDefine<ItemDefine>();
    ret->id = this->role_->getDefine()->id;
    ret->dbID = this->idGenerator_.require();
    ret->cell = cell;
    ret->count = num;
    ret->itemID = itemID;
    ret->position = position;
    ret->borntime = Basic::Time_::localTimeString().c_str();
    this->objects_[index] = ret;
    return ret;
}

void ItemSystem::refresh(int dbID, int count, GameDefine::ItemRefreshReason reason /*= GameDefine::ItemRefreshReason_None*/) {
}

bool ItemSystem::sell(int dbID, GameDefine::ItemSellSource source /*= GameDefine::ItemSellSource_Invalid*/) {
    throw new std::exception();
}

bool ItemSystem::useItem(int dbID, int num /*= 1*/) {
    throw new std::exception();
}

bool ItemSystem::moveItem(int dbID, GameDefine::ItemLocation locationSrc, int xSrc, GameDefine::ItemLocation locationDst, int xDst) {
    throw new std::exception();
}

void ItemSystem::onTimer(Basic::Timer* timer) {
    if (timer == this->testTimer_.lock().get()) {
        auto position = this->getFirstEmptySlot(GameDefine::ObjectCellType_Bag);
        if (position == -1)
            return;
        auto& records = ItemTable::getInstance()->all();
        if (records.size() == 0)
            return;
        auto index = Basic::Random::getInstance().randI(0, records.size() - 1);
        auto& record = records[index];
        auto item = create(record->ID, Basic::Random::getInstance().randI(1, 100), GameDefine::ObjectCellType::ObjectCellType_Bag, position);
        if (item) {
            Cmd::RetObjectAdd cmd;
            auto* obj = cmd.add_objects();
            obj->set_dbid(item->dbID);
            obj->set_itemid(item->itemID);
            obj->set_count(item->count);
            obj->set_cell((GameDefine::ObjectCellType)item->cell);
            obj->set_position(position);
            SendProtoBuffer(this->role_->getNetInterface(), Cmd::SERVERID::RTObject_Add, cmd);
        }
    }
}

void ItemSystem::onTimerEnd(Basic::Timer * timer) {
}


void ItemSystem::syncToClient() {
    Cmd::RetObjectAdd cmd;
    for (auto& it : this->objects_) {
        if (it && it->dbID > 0) {
            auto obj = cmd.add_objects();
            obj->set_dbid(it->dbID);
            obj->set_itemid(it->itemID);
            obj->set_count(it->count);
            obj->set_cell((GameDefine::ObjectCellType)it->cell);
            obj->set_position(it->position);
        }
    }
    SendProtoBuffer(this->role_->getNetInterface(), Cmd::SERVERID::RTObject_Add, cmd);
}
void ItemSystem::pullFromDB() {
    std::vector<DBDefine*> records;
    App::DataBase.executer().pullByKey1(ItemDefine::GetDefine(), this->role_->getDefine()->id,
                                        ItemDefine::Create, records);
    for (auto it : records) {
        auto def = (ItemDefine*)it;
        auto index = getIndex((GameDefine::ObjectCellType)def->cell, def->position);
        if (index == -1 || index >= ItemDefine::ObjectsCapacity) {
            delete it;
        }
        this->objects_[index] = def;
    }
    for(auto it : this->objects_) {
        if (it && it->dbID > 0) {
            this->idGenerator_.add(it->dbID);
        }
    }
}


void ItemSystem::testSystem() {
    if (!this->testTimer_.expired())
        this->testTimer_.lock()->cancel();
    this->testTimer_ = Timers::getInstance()->repeat(5000, &ItemSystem::onTimer, this, 15 * 1000, &ItemSystem::onTimerEnd);
}

int ItemSystem::getFirstEmptySlot(GameDefine::ObjectCellType cell) {
    int start = getStartIndex(cell);
    auto end = start + this->sCellCapicity[cell - 1];
    for (auto i = start; i < end; ++i) {
        auto& obj = this->objects_[i];
        if (!obj || obj->dbID == 0)
            return i;
    }
    return -1;
}

bool ItemSystem::empty(GameDefine::ObjectCellType cell) {
    return getFirstEmptySlot(cell) == -1;
}

int ItemSystem::getStartIndex(GameDefine::ObjectCellType cell) {
    if (cell > GameDefine::ObjectCellType::ObjectCellType_None && cell <= GameDefine::ObjectCellType::ObjectCellType_Store) {
        int count = 0;
        for (int i = 0; i < cell - 1; ++i)
            count += this->sCellCapicity[i];
        return count;
    }
    assert(false);
    return -1;
}

int ItemSystem::getIndex(GameDefine::ObjectCellType cell, int position) {
    auto start = getStartIndex(cell);
    if (start == -1)
        return -1;
    return start + position;
}

