#ifndef OptionService_h__
#define OptionService_h__

#include "IService.h"
#include "../json/JsonReader.h"
#include "../basic/FileLoader.h"

class OptionService:public IService<OptionService> {
  public:
    OptionService();
    ~OptionService();
    virtual const char * name() override;
    virtual bool start() override;
    template<typename T>
    bool getOption(const char* type, T& ret);
    template<typename T>
    bool getOption(const char* type, int index, T& ret);
    template<typename T>
    bool getOption(const char* type, const char* name, T& ret);
  private:
    Basic::FileLoader loader_;
    rapidjson::Document root_;
};

template<typename T>
bool OptionService::getOption(const char* type, T& ret) {
    auto& categroy = root_[type];
    if (categroy.IsObject()) {
        Serializer::JsonReader::read(&root_[type], ret);
        return true;
    }
    return true;
}

template<typename T>
bool OptionService::getOption(const char* type, int index, T& ret) {
    return true;
}

template<typename T>
bool OptionService::getOption(const char* type, const char* name, T& ret) {
    auto& categroy = root_[type];
    if (categroy.IsObject()) {
        auto& option = categroy[name];
        if (option.IsObject()) {
            Serializer::JsonReader::read(&option, ret);
            return true;
        }
    }
    return true;
}
#endif // OptionService_h__
