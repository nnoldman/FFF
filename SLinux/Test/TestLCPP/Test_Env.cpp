#include "Test_Env.h"
#include "Environment.h"
#include <iostream>



Test_Env::Test_Env() {
    Environment::start();
    Environment env;
    std::cout << "App currentWorkDirectory:" << env.appStoreDirectory() << std::endl;
    std::cout << "App getAppName:" << env.getAppName() << std::endl;
    std::cout << "App getAppFullName:" << env.getAppFileFullName() << std::endl;
    std::cout << "App currentWorkDirectory:" << env.currentWorkDirectory() << std::endl;

    env.setCurrentWorkDirectory("../../");
    std::cout << "-------------------------" << std::endl;

    std::cout << "App currentWorkDirectory:" << env.appStoreDirectory() << std::endl;
    std::cout << "App getAppName:" << env.getAppName() << std::endl;
    std::cout << "App getAppFullName:" << env.getAppFileFullName() << std::endl;
    std::cout << "App currentWorkDirectory:" << env.currentWorkDirectory() << std::endl;
}


Test_Env::~Test_Env() {
}
