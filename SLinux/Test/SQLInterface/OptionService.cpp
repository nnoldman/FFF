#include "stdafx.h"
#include "OptionService.h"
#include "rapidjson/error/en.h"
OptionService::OptionService() {
}


OptionService::~OptionService() {
}

bool OptionService::start() {
    auto path = "config.json";
    ifstream ifs(path);
    if (ifs) {
        ifs.seekg(0, ios::end);
        size_t length = ifs.tellg();
        ifs.seekg(0, ios::beg);
        char* buffer = new char[length];
        memset(buffer, 0, length);
        auto& ret = ifs.read(buffer, length);
        if (ret) {
            ifs.close();
        }
        ParseResult ok = root_.Parse<0>(buffer);
        if (!ok) {
            printf("Json Parse Error: %s (Position:%u)", rapidjson::GetParseError_En(ok.Code()), ok.Offset());
            return false;
        }
    }
    return false;
}
