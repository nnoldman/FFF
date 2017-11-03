#ifndef SystemMessageController_h__
#define SystemMessageController_h__
#include "GameSystems/GameControllerBase.h"
#include "Cmd.pb.h"
#include "Command.pb.h"
class Role;
class MessageController :
    public GameController<MessageController>
{
public:
    MessageController();
    ~MessageController();

    void onUserEnterWorld(Role* role);
    void sendMessage(Cmd::MessageChannel channel, const string& content, Role* role);
    void sendMessage(Cmd::MessageChannel channel, const string& content, Role* role, const string& sender);
    void broadcast(Cmd::MessageChannel channel, const string& content);
    void broadcast(Cmd::MessageChannel channel, const string& content, const string& sender);
protected:
    static const string sSenderNameSystem;
    static const string sSenderNameGM;
};

#endif // SystemMessageController_h__
