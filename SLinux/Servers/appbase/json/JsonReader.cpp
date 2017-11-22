#include "../appbase.h"
#include "JsonReader.h"
namespace Serializer {
    JsonReader::JsonReader() {
    }

    JsonReader::~JsonReader() {
    }


    void JsonReader::read(Value* var, int& value) {
        if (var->IsInt())
            value = var->GetInt();
    }

    void JsonReader::read(Value* var, bool& value) {
        if (var->IsBool())
            value = var->GetBool();
    }

    void JsonReader::read(Value* var, char& value) {
        if (var->IsInt())
            value = (char) var->GetInt();
    }

    void JsonReader::read(Value* var, unsigned int& value) {
        if (var->IsUint())
            value = var->GetUint();
    }

    void JsonReader::read(Value* var, int64_t& value) {
        if (var->IsInt64())
            value = var->GetInt64();
    }

    void JsonReader::read(Value* var, uint64_t& value) {
        if (var->IsUint64())
            value = var->GetUint64();
    }

    void JsonReader::read(Value* var, double& value) {
        if (var->IsDouble())
            value = var->GetDouble();
    }

    void JsonReader::read(Value* var, string& value) {
        if(var->IsString())
            value = var->GetString();
    }
}
