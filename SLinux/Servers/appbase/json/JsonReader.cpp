#include "../appbase.h"
#include "JsonReader.h"
namespace Serializer {
    JsonReader::JsonReader() {
    }

    JsonReader::~JsonReader() {
    }


    void JsonReader::read(Value* var, int& value) {
        value = var->GetInt();
    }

    void JsonReader::read(Value* var, bool& value) {
        value = var->GetBool();
    }

    void JsonReader::read(Value* var, char& value) {
        value = (char) var->GetInt();
    }

    void JsonReader::read(Value* var, unsigned int& value) {
        value = var->GetUint();
    }

    void JsonReader::read(Value* var, int64_t& value) {
        value = var->GetInt64();
    }

    void JsonReader::read(Value* var, uint64_t& value) {
        value = var->GetUint64();
    }

    void JsonReader::read(Value* var, double& value) {
        value = var->GetDouble();
    }

    void JsonReader::read(Value* var, string& value) {
        value = var->GetString();
    }
}
