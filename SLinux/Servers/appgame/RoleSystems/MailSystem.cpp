#include "stdafx.h"
#include "MailSystem.h"
#include "App.h"



MailSystem::MailSystem()
{
}


MailSystem::~MailSystem()
{
}


void MailSystem::initialize(Role* role)
{
    SystemBase::initialize(role);
    this->pullFromDB();
}

void MailSystem::onNet(Cmd::CLIENTID id, ProtocoBuffer* pb)
{
}

void MailSystem::archieve()
{
}

void MailSystem::onTimer(Basic::Timer* timer)
{
    throw std::logic_error("The method or operation is not implemented.");
}

void MailSystem::onTimerEnd(Basic::Timer* timer)
{
}

void MailSystem::pullFromDB()
{
    std::list<DBDefine*> records;
    App::DataBase.pullByPrimaryKey(MailDefine::GetDefine(), this->role_->getDefine()->id,
                                   MailDefine::Create, records);
}