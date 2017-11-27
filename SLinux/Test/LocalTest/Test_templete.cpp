#include "stdafx.h"
#include "Test_templete.h"
#include "Installer.h"


Test_templete::Test_templete() {
}
Test_templete::~Test_templete() {
}

ControllerBase::ControllerBase() {

}

ControllerBase::~ControllerBase() {

}

Function(test_templete) {

    NetController* controller = NetController::createInstance();
    NetController::get()->initialize();
}

bool NetController::initialize() {
    return true;
}
