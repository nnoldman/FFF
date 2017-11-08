#include "stdafx.h"
#include "JsonWriter.h"
namespace Serializer
{
    JsonWriter::JsonWriter()
        : writer_(buffer_)
    {
    }

    JsonWriter::~JsonWriter()
    {
    }

    void JsonWriter::write(int var)
    {
        this->writer_.Int(var);
    }

    void JsonWriter::write(bool var)
    {
        this->writer_.Bool(var);
    }

    void JsonWriter::write(unsigned int var)
    {
        this->writer_.Uint(var);
    }

    void JsonWriter::write(int64_t var)
    {
        this->writer_.Int64(var);
    }

    void JsonWriter::write(uint64_t var)
    {
        this->writer_.Uint64(var);
    }

    void JsonWriter::write(double var)
    {
        this->writer_.Double(var);
    }

    void JsonWriter::write(const char* var)
    {
        this->writer_.String(var);
    }

    void JsonWriter::write(const string& var)
    {
        this->writer_.String(var.c_str());
    }

    void JsonWriter::write(char var)
    {
        this->writer_.Int(var);
    }

    JsonWriter& JsonWriter::key(const char * var)
    {
        this->writer_.Key(var);
        return *this;
    }

    bool JsonWriter::startObject()
    {
        return this->writer_.StartObject();
    }

    bool JsonWriter::endObject()
    {
        return this->writer_.EndObject();
    }

    bool JsonWriter::startArray()
    {
        return this->writer_.StartArray();
    }

    bool JsonWriter::endArray()
    {
        return this->writer_.EndArray();
    }

    const char * JsonWriter::text()
    {
        return this->buffer_.GetString();
    }

}


