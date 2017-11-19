#ifndef Interface_h__
#define Interface_h__
#include <vector>
#include <string>
namespace Serializer {
    class SerializerInterface {
      public:
        template<typename T>
        bool fromText(const std::vector<std::string>& record, T& ret);
        template<typename T>
        bool toText(const T& obj);
    };
}


#endif // Interface_h__
