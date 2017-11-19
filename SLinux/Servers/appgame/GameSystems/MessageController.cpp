#include "../appgame.h"
#include "MessageController.h"
#include "Role.h"
#include "App.h"
#include "Config/Language.h"

const string MessageController::sSenderNameSystem = "ϵͳ";
const string MessageController::sSenderNameGM = "GM";

MessageController::MessageController() {
}


MessageController::~MessageController() {
}


void MessageController::onUserEnterWorld(Role* role) {
    FORMAT_TEXT(buffer, Language::getInstance()->getContent(100).c_str(), role->getDefine()->base.name.c_str());
    printf("FORMAT_TEXT:%s", Language::getInstance()->getContent(100).c_str());
    this->sendMessage(Cmd::MessageChannel::MessageChannel_System_TV, buffer, role);
}

void MessageController::sendMessage(Cmd::MessageChannel channel, const string& content, Role* role) {
    this->sendMessage(channel, content, role, sSenderNameSystem);
}

void MessageController::sendMessage(Cmd::MessageChannel channel, const string& content, Role* role, const string& sender) {
    assert(role);
    Cmd::RetMessage message;
    message.set_channel(channel);
    message.set_content(content);
    message.set_sender(sender);
    message.set_localtime(Basic::Time_::local());
    SendProtoBuffer(role->getNetInterface(), Cmd::RTMessage, message);
}

void MessageController::broadcast(Cmd::MessageChannel channel, const string& content) {
    this->broadcast(channel, content, sSenderNameSystem);
}

void MessageController::broadcast(Cmd::MessageChannel channel, const string& content, const string& sender) {
    auto accounts = WorldService::get()->getAcccounts();
    for (auto it : accounts) {
        this->sendMessage(channel, content, (Role*)it.second, sender);
    }
}


