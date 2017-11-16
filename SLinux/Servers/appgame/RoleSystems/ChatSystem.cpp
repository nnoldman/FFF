#include "../stdafx.h"
#include "ChatSystem.h"
#include "GameSystems/MessageController.h"



ChatSystem::ChatSystem() {
}


ChatSystem::~ChatSystem() {
}

void ChatSystem::initialize(Role* role) {
    SystemBase::initialize(role);
}

void ChatSystem::onNet(Cmd::CLIENTID id, ProtocoBuffer* pb) {
    switch (id) {
    case Cmd::RQChat: {
        auto req = pb->parse<Cmd::ReqChat>();
        if (req->channel() == Cmd::MessageChannel::MessageChannel_User_World) {
            this->onWorldMessage(req.get());
        }
    }
    break;
    default:
        break;
    }
}

void ChatSystem::onWorldMessage(Cmd::ReqChat* message) {
    MessageController::getInstance()->broadcast(Cmd::MessageChannel_User_World, message->content(), message->from());
}

void ChatSystem::onTimer(Basic::Timer* timer) {
}

void ChatSystem::onTimerEnd(Basic::Timer* timer) {
}
