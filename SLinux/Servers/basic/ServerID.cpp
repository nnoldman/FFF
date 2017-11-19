#include "base.h"
#include "ServerID.h"
namespace Basic {
    const std::string& ServerID::get() {
        return id_;
    }

    void ServerID::set(const char* id) {
        id_ = id;
    }
    std::string ServerID::id_ = "0";
}
