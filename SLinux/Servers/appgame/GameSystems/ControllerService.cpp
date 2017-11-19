#include "../appgame.h"
#include "ControllerService.h"
#include "MessageController.h"

ControllerService::ControllerService() {
}

ControllerService::~ControllerService() {
    dSafeDeleteVector(this->controllers_);
}

const char* ControllerService::name() {
    return "GameControllers";
}

bool ControllerService::start() {
    add<MessageController>();
    return true;
}

void ControllerService::tick() {
    for (auto it : this->controllers_) {
        it->update();
    }
}
