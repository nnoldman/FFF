#include "../appgame.h"
#include "SystemBase.h"

SystemBase::SystemBase() {
}


SystemBase::~SystemBase() {
}



void SystemBase::initialize(Role* role) {
    this->role_ = role;
}

void SystemBase::onNet(Cmd::CLIENTID id, ProtocoBuffer * pb) {
}

void SystemBase::archieve() {
}


void SystemBase::send(Cmd::SERVERID id, google::protobuf::MessageLite * message) {
    BundleSender::GetInstance().sendProtoBuffer((u32)id, message, role_->getNetInterface());
}

void SystemBase::onTimer(Basic::Timer * timer) {
}

void SystemBase::onTimerEnd(Basic::Timer * timer) {
}
