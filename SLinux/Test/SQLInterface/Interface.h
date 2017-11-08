namespace Serializer
{
    class Interface
    {
    public:
        template<typename T>
        bool fromText(const std::vector<string>& record, T& ret);
        template<typename T>
        bool toText(const T& obj);
    };

    template<typename T>
    bool Serializer::Interface::toText(const T& obj)
    {
    }

    template<typename T>
    bool Serializer::Interface::fromText(const std::vector<string>& record, T& ret)
    {
    }

}


