#ifndef JsonReader_h__
#define JsonReader_h__
#include "rapidjson/rapidjson.h"
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include <sstream>
#include <string>
#include <vector>
using namespace rapidjson;
using namespace std;
namespace Serializer {
    class JsonReader {
      public:
        JsonReader();
        ~JsonReader();
        template<typename T>
        bool fromText(string text, T& ret);

        template<typename T>
        static void read(Value* serializer, const char* key, T& value);

        static void read(Value* var, int& value);
        static void read(Value* var, bool& value);
        static void read(Value* var, char& value);
        static void read(Value* var, unsigned int& value);
        static void read(Value* var, int64_t& value);
        static void read(Value* var, uint64_t& value);
        static void read(Value* var, double& value);
        static void read(Value* var, string& value);

        template<typename T>
        static void read(Value* var, T& value);

        template<typename T, int N>
        static void read(Value* var, T(&value)[N]);
        template<typename T>
        static void read(Value* var, std::vector<T>& value);
    };

    template<typename T>
    void Serializer::JsonReader::read(Value* var, std::vector<T>& value) {
        value.clear();
        auto& arr = var->GetArray();
        for (auto i = 0U; i < arr.Size(); ++i) {
            auto& it = arr[i];
            T t;
            read(&it, t);
            value.push_back(t);
        }
    }

    template<typename T, int N>
    void Serializer::JsonReader::read(Value* var, T(&value)[N]) {
        auto& arr = var->GetArray();
        for (auto i = 0U; i < N && i < arr.Size(); ++i) {
            auto& it = arr[i];
            read(&it, value[i]);
        }
    }

    template<typename T>
    void Serializer::JsonReader::read(Value* var, T& value) {
        value.fromText(var);
    }

    template<typename T>
    bool Serializer::JsonReader::fromText(string text, T& ret) {
        Document doc;
        doc.Parse<0>(text.c_str());
        read(&doc, ret);
        return true;
    }

    template<typename T>
    inline void JsonReader::read(Value * serializer, const char * key, T & value) {
        JsonReader::read(&((*serializer)[key]), value);
    }

}
#define __BeginReader void fromText(Value* serializer)
#define __Read(member) Serializer::JsonReader::read(serializer, #member, member)
#endif // JsonReader_h__
