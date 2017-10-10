#include "stdafx.h"
#include "LoginNetAgent.h"
#include "Account.h"
#include "Command.pb.h"
#include "Cmd.pb.h"
#include "GlobalAccountDefine.h"
LoginNetAgent::LoginNetAgent()
{
}
LoginNetAgent::~LoginNetAgent()
{
    App::Net.onMessage.remove(&::LoginNetAgent::onMessage, this);
    App::Net.onDisconnect.remove(&::LoginNetAgent::onDisconnect, this);
}

bool LoginNetAgent::initialize()
{
    App::Net.onMessage.add(&::LoginNetAgent::onMessage, this);
    App::Net.onDisconnect.add(&::LoginNetAgent::onDisconnect, this);
    return true;
}

void LoginNetAgent::onMessage(ProtocoBuffer* pb, Connection* connect)
{
    switch (pb->opcode)
    {
    case Cmd::CLIENTID::RQAccountOperation:
        {
            auto req = pb->parse<Cmd::ReqAccountOperation>();

            if (req->action() == Cmd::AccountAction::AccountAction_Create)
            {
                on_rqCreateAccount(req->user(), req->password(), connect);
            }
            else if (req->action() == Cmd::AccountAction::AccountAction_Rename)
            {
                on_rqRenameAccount(req->user(), req->password(), connect);
            }
            else if (req->action() == Cmd::AccountAction::AccountAction_Delete)
            {
                on_rqDeleteAccount(req->user(), req->password(), connect);
            }
            else if (req->action() == Cmd::AccountAction::AccountAction_Login)
            {
                on_rqLoginAccount(req->user(), req->password(), connect);
            }
        }
        break;
    default:
        break;
    }
}

void LoginNetAgent::onDisconnect(Connection* connection)
{
    mClients.erase(connection);
}

bool LoginNetAgent::on_rqLoginAccount(const string& user, const string& password, Connection* con)
{
    Account* gateAccount = new Account();
    gateAccount->initialize();
    gateAccount->setConnection(con);
    auto def = gateAccount->getDefine();
    def->user = user.c_str();

    if (def->pull(def->user.c_str()))
    {
        if (def->password != password.c_str())
        {
            Cmd::RetAccountOperation ret;
            ret.set_error(Cmd::AccountErrorCode::AccountErrorCode_PasswordError);
            SendProtoBuffer(con->getSocket(), Cmd::SERVERID::RTAccountOperation, ret);
            dSafeDelete(gateAccount);
            return false;
        }
        else
        {
            onLoginSucess(gateAccount, con);
        }
    }
    else
    {
        if (App::Config.login.db.autoCreateAccount)
        {
            def->password = password.c_str();
            if (def->insertAndQuery(def->user.c_str()))
            {
                onLoginSucess(gateAccount, con);
            }
        }
        else
        {
            Cmd::RetAccountOperation ret;
            ret.set_error(Cmd::AccountErrorCode::AccountErrorCode_UserCantFind);
            SendProtoBuffer(con->getSocket(), Cmd::SERVERID::RTAccountOperation, ret);
            dSafeDelete(gateAccount);
            return false;
        }
    }
    return true;
}

bool LoginNetAgent::on_rqCreateAccount(const string& user, const string& password, Connection* con)
{
    Account* gateAccount = new Account();
    gateAccount->setConnection(con);
    auto def = (GlobalAccountDefine*)gateAccount->getDBInterface();
    if (def->pull(user.c_str()))
    {
        Cmd::RetAccountOperation ret;
        ret.set_error(Cmd::AccountErrorCode::AccountErrorCode_NameRepeated);
        SendProtoBuffer(con->getSocket(), Cmd::SERVERID::RTAccountOperation, ret);
        dSafeDelete(gateAccount);
        return false;
    }
    else
    {
        def->user = user.c_str();
        def->password = password.c_str();
        auto queryRet = def->insertAndQuery(user.c_str());
        assert(queryRet);
        gateAccount->setGlobalID(def->id);

        Cmd::RetAccountOperation ret;
        ret.set_error(Cmd::AccountErrorCode::AccountErrorCode_CreateSucessed);
        ret.set_accountid(def->id);
        SendProtoBuffer(con->getSocket(), Cmd::SERVERID::RTAccountOperation, ret);

        dSafeDelete(gateAccount);
        //App::Gate.onEnter(gateAccount);

        return true;
    }
}
bool LoginNetAgent::on_rqDeleteAccount(const string& user, const string& password, Connection* con)
{
    return false;
}

bool LoginNetAgent::on_rqRenameAccount(const string& user, const string& password, Connection* con)
{
    return false;
}

void LoginNetAgent::onLoginSucess(Account* account, Connection* con)
{
    auto def = (GlobalAccountDefine*)account->getDBInterface();
    account->setGlobalID(def->id);
    Cmd::RetAccountOperation ret;
    ret.set_error(Cmd::AccountErrorCode::AccountErrorCode_LoginSucessed);
    ret.set_accountid(def->id);
    ret.set_time(Basic::Time_::utc());
    ret.set_token(Encrypt::makeLoginToken(def->id, ret.time()));
    ret.add_late_serverids(def->late_serverid1);
    ret.add_late_serverids(def->late_serverid2);
    ret.add_late_serverids(def->late_serverid3);
    SendProtoBuffer(con->getSocket(), Cmd::SERVERID::RTAccountOperation, ret);
    dSafeDelete(account);
}

bool LoginNetAgent::createAccount(string user, string psd, Connection* con)
{
    return false;
}

