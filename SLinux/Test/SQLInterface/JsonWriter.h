#ifndef JsonWriter_h__
#define JsonWriter_h__

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include <list>
namespace Serializer {
    class JsonWriter {
      public:
        JsonWriter();
        ~JsonWriter();

        template<typename T>
        static void write(JsonWriter& writer, const char* key, const T& value);

        void write(int var);
        void write(bool var);
        void write(char var);
        void write(unsigned int var);
        void write(int64_t var);
        void write(uint64_t var);
        void write(double var);
        void write(const char* var);
        void write(const string& var);

        template<typename T>
        void write(const T& obj);
        template<typename T, int N>
        void write(const T(&arr)[N]);

        template<typename T>
        void write(const std::vector<T>& arr);

        template<typename T>
        void write(const std::list<T>& arr);

        JsonWriter& key(const char* var);
        const char* text();
      private:
        bool startObject();
        bool endObject();
        bool startArray();
        bool endArray();
      private:
        rapidjson::StringBuffer buffer_;
        rapidjson::Writer<rapidjson::StringBuffer> writer_;
    };

    template<typename T>
    void Serializer::JsonWriter::write(const std::list<T>& arr) {
        this->startArray();
        for (auto& it : arr)
            this->write(it);
        this->endArray();
    }

    template<typename T>
    void Serializer::JsonWriter::write(const std::vector<T>& arr) {
        this->startArray();
        for (auto& it : arr)
            this->write(it);
        this->endArray();
    }

    template<typename T, int N>
    void Serializer::JsonWriter::write(const T(&arr)[N]) {
        this->startArray();
        for (int i = 0; i < N; ++i)
            this->write(arr[i]);
        this->endArray();
    }
    template<typename T>
    inline void JsonWriter::write(JsonWriter & serializer, const char * key, const T & value) {
        serializer.key(key).write(value);
    }
    template<typename T>
    void Serializer::JsonWriter::write(const T& obj) {
        if (this->startObject()) {
            obj.toText(*this);
            this->endObject();
        }
    }

}


#endif // JsonWriter_h__
