#pragma once

#include "Array.h"
#include "StringHelper.h"
namespace Basic {
    class CommandLine {
      public:
        CommandLine(int narg, char* argv[]);
        ~CommandLine();

        template<typename T>
        void get(const char* key, T& v) {
            auto it = this->args_.find(key);
            if (it != this->args_.end())
                StringHelper::setValue(it->second.c_str(), &v);
        }
        size_t arg_count();
      private:
        map<std::string, std::string> args_;
    };
}
