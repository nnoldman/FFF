#ifndef OptionService_h__
#define OptionService_h__

#include "JsonReader.h"

class OptionService {
  public:
    OptionService();
    ~OptionService();
    virtual bool start();
    template<typename T>
    bool getOption(const char* type, T& ret);
    template<typename T>
    bool getOption(const char* type, int index, T& ret);
    template<typename T>
    bool getOption(const char* type, const char* name, T& ret);
  private:
    rapidjson::Document root_;
};

template<typename T>
bool OptionService::getOption(const char* type, T& ret) {
    auto categroy = std::move(root_[type]);
    Serializer::JsonReader::read(&root_[type], ret);
    return true;
}

template<typename T>
bool OptionService::getOption(const char* type, int index, T& ret) {
    return true;
}

template<typename T>
bool OptionService::getOption(const char* type, const char* name, T& ret) {
    auto& categroy = root_[type];
    auto& option = categroy[name];
    Serializer::JsonReader::read(&option, ret);
    return true;
}
#endif // OptionService_h__
