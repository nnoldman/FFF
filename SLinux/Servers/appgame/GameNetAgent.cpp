#include "stdafx.h"
#include "GameNetAgent.h"
#include "Command.pb.h"
#include "Cmd.pb.h"
#include "md5.h"
#include "GameUser.h"
#include "TableDefine/GameUserDefine.h"
#include "Role.h"

GameNetAgent::GameNetAgent()
{
}


GameNetAgent::~GameNetAgent()
{
    App::Net.onMessage.remove(&::GameNetAgent::onMessage, this);
    App::Net.onDisconnect.remove(&::GameNetAgent::onDisconnect, this);
}

bool GameNetAgent::initialize()
{
    App::Net.onMessage.add(&::GameNetAgent::onMessage, this);
    App::Net.onDisconnect.add(&::GameNetAgent::onDisconnect, this);
    return true;
}

void GameNetAgent::onDisconnect(Connection* connection)
{
    App::World.reclaimAccount(connection);
}

void GameNetAgent::onMessage(ProtocoBuffer* pb, Connection* connect)
{
    switch (pb->opcode)
    {
    case Cmd::CLIENTID::RQLoginGame:
    {
        auto req = pb->parse<Cmd::ReqLoginGameServer>();
        Cmd::RetLoginGameServer ret;
        if (Encrypt::makeLoginToken(req->accountid(), req->time()) != req->token())
        {
            ret.set_error(Cmd::LoginGameError::LoginGameInvalid);
        }
        else if (req->time() + 600 < Basic::Time_::utc())
        {
            ret.set_error(Cmd::LoginGameError::LoginGameOverdue);
        }
        else
        {
            auto user = new GameUser();
            user->initialize();
            user->setGlobalID(req->accountid());
            user->getDefine()->setGlobalID(req->accountid());
            user->onEnterGate();
            auto role = user->getRole();
            auto gameRole = ret.mutable_role();
            auto def = role->getDefine();
            gameRole->set_id(def->id);
            if (role->valid())
            {
                gameRole->set_vip(def->base.vip);
                gameRole->set_level(def->base.level);
                gameRole->set_job(def->base.job);
                gameRole->set_sex(def->base.sex);
                gameRole->set_name(def->base.name.c_str());
            }
            App::World.onEnterWorld(connect, user);
            ret.set_error(Cmd::LoginGameError::LoginGameSucess);
        }
        SendProtoBuffer(connect, Cmd::RTLoginGame, ret);
    }
    break;
    case Cmd::CLIENTID::RQCreateRole:
    {
        auto req = pb->parse<Cmd::ReqCreateRole>();
        auto user = (GameUser*)App::World.get(connect);
        if (user)
        {
            auto role = user->getRole();
            if (role)
            {
                Cmd::RetCreateRole ret;
                auto gameRole = ret.mutable_role();
                auto def = role->getDefine();
                def->base.name = req->name().c_str();
                def->base.borntime = Basic::Time_::localTimeString().c_str();
                if (def->exist(def->key2(), def->base.name.c_str()))
                {
                    ret.set_error(Cmd::CreateRoleError::CreateRoleNameRepeated);
                    SendProtoBuffer(connect, Cmd::RTCreateRole, ret);
                }
                else
                {
                    def->base.sex = req->sex();
                    def->base.job = req->job();
                    //if (!def->insertAndQuery(def->key2(), def->name.c_str()))
                    if (!def->insertAndQuery(def->key2(), def->base.name.c_str()))
                    {
                        assert(false);
                    }
                    else
                    {
                        user->getDefine()->role = def->id;
                        if (!user->getDefine()->commitByKey1())
                        {
                            assert(false);
                        }
                        gameRole->set_id(def->id);
                        if (role->valid())
                        {
                            gameRole->set_vip(def->base.vip);
                            gameRole->set_level(def->base.level);
                            gameRole->set_job(def->base.job);
                            gameRole->set_sex(def->base.sex);
                            gameRole->set_name(def->base.name.c_str());
                        }
                        ret.set_error(Cmd::CreateRoleError::CreateRoleSucess);
                        SendProtoBuffer(connect, Cmd::RTCreateRole, ret);
                    }
                }
            }
        }
    }
    break;
    case Cmd::CLIENTID::RQEnterGame:
    {
        auto user = (GameUser*)App::World.get(connect);
        if(user)
            user->activeRole();
    }
    break;
    default:
    {
        if (pb->opcode > Cmd::RQRoleBaseOperation && pb->opcode < Cmd::RQRoleBaseOperationEnd)
        {
            auto user = (GameUser*)App::World.get(connect);
            auto activerole = user->getRole();
            if (activerole != nullptr)
            {
                activerole->onNet((Cmd::CLIENTID)pb->opcode, pb);
            }
        }
        break;
    }
    }
}


bool GameNetAgent::on_rqCreateAccount(const string & user, const string & password, Connection * con)
{
    return false;
}


bool GameNetAgent::on_rqLoginAccount(string user, string psw, Connection * con)
{
    return false;
}

void GameNetAgent::onLoginSucess(Account * account)
{
}

