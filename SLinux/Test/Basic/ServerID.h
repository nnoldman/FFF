#pragma once
#include <string>
class ServerID {
  public:
    static const std::string& get();
    static void set(const char* id);
  private:
    static std::string id_;
};

