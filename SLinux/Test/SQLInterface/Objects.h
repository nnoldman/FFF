#ifndef Objects_h__
#define Objects_h__

#include "JsonWriter.h"
#include "JsonReader.h"
#include <functional>

#define __BeginReader void fromText(Value* serializer)
#define __Read(member) JsonReader::read(serializer, #member, member)
#define __BeginWriter void toText(Serializer::JsonWriter* serializer) const
#define __Write(member) JsonWriter::write(serializer, #member, member)

#define __IOBegin void process(Serializer::JsonWriter* writer, Value* reader)\
    {\
        vector<std::function<void()>>* readers;\
        vector<std::function<void()>>* writers;\
        if (writer)\
            writers = new vector<std::function<void()>>();\
        else\
            readers = new vector<std::function<void()>>();

#define __IOMember(member) \
    if (writer)\
    {\
        writers->push_back([this, writer, reader]()\
        {\
            JsonWriter::write(writer, #member, member);\
        });\
    }\
    if (reader)\
    {\
        readers->push_back([this, writer, reader]()\
        {\
            JsonReader::read(reader, #member, member);\
        });\
    }

#define __IOEnd \
    if (writer)\
    {\
        for (auto it : *writers)\
        {\
            it();\
        }\
    }\
    if (reader)\
    {\
        for (auto it : *readers)\
        {\
            it();\
        }\
    }\
    }

using namespace Serializer;
namespace Objects {
    struct Equip {
        int id;
        string name;
        char quality;

        //__BeginReader
        //{
        //    __Read(id);
        //    __Read(name);
        //    __Read(quality);
        //}
        //__BeginWriter
        //{
        //    __Write(id);
        //    __Write(name);
        //    __Write(quality);
        //}

        //__IOBegin
        //__IOMember(id)
        //__IOMember(name)
        //__IOMember(quality)
        //__IOEnd
        void toText(Serializer::JsonWriter& serializer) const {
            JsonWriter::write(serializer, "id", this->id);
            JsonWriter::write(serializer, "name", this->name);
            JsonWriter::write(serializer, "quality", this->quality);
        }
        void fromText(Value* serializer) {
            JsonReader::read(serializer, "id", this->id);
            JsonReader::read(serializer, "name", this->name);
            JsonReader::read(serializer, "quality", this->quality);
        }

        //void process(Serializer::JsonWriter* writer, Value* reader)
        //{
        //    vector<std::function<void()>>* readers;
        //    vector<std::function<void()>>* writers;
        //    if (writer)
        //        writers = new vector<std::function<void()>>();
        //    else
        //        readers = new vector<std::function<void()>>();
        //    if (writer)
        //    {
        //        writers->push_back([this, writer, reader]()
        //        {
        //            JsonWriter::write(writer, "id", this->id);
        //        });
        //    }
        //    if (reader)
        //    {
        //        readers->push_back([this, writer, reader]()
        //        {
        //            JsonReader::read(reader, "id", this->id);
        //        });
        //    }
        //    readers->push_back([this, writer, reader]()
        //    {
        //        JsonReader::read(reader, "name", this->name);
        //    });
        //    writers->push_back([this, writer, reader]()
        //    {
        //        JsonWriter::write(writer, "name", this->name);
        //    });
        //    readers->push_back([this, writer, reader]()
        //    {
        //        JsonReader::read(reader, "quality", this->quality);
        //    });
        //    writers->push_back([this, writer, reader]()
        //    {
        //        JsonWriter::write(writer, "quality", this->quality);
        //    });
        //    if (writer)
        //    {
        //        for (auto it : *writers)
        //        {
        //            it();
        //        }
        //    }
        //    if (reader)
        //    {
        //        for (auto it : *readers)
        //        {
        //            it();
        //        }
        //    }
        //}
    };

#define dMemoryZeroArray(arr) memset(arr,0,sizeof(arr))

    struct Role {
        int id;
        string name;
        Equip equips[4];
        int ids[8];
        vector<Equip> equips2;
        Role() {
            dMemoryZeroArray(ids);
        }
        //__IOBegin
        //__IOMember(id)
        //__IOMember(name)
        //__IOMember(equips)
        //__IOMember(ids)
        //__IOMember(equips2)
        //__IOEnd

        void toText(Serializer::JsonWriter& serializer) const {
            JsonWriter::write(serializer, "id", this->id);
            JsonWriter::write(serializer, "name", this->name);
            JsonWriter::write(serializer, "equips", this->equips);
            JsonWriter::write(serializer, "ids", this->ids);
            JsonWriter::write(serializer, "equips2", this->equips2);
        }
        void fromText(Value* serializer) {
            JsonReader::read(serializer, "id", this->id);
            JsonReader::read(serializer, "name", this->name);
            JsonReader::read(serializer, "equips", this->equips);
            JsonReader::read(serializer, "ids", this->ids);
            JsonReader::read(serializer, "equips2", this->equips2);
        }
    };
}

#endif // Objects_h__
