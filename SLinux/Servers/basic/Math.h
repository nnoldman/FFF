#ifndef Math_h__
#define Math_h__
#include <sstream>
namespace Basic
{
    class Math
    {
    public:
        template<typename T>
        T dScale(T src, T reference, double scale);

        template<typename T>
        T dClamp(T src, T minv, T maxv);
        int dRound(double src, int base = 1);

        static void toHEX(unsigned char* arr, size_t count, std::string& stream);
        static void fromHEX(unsigned char* arr, size_t count, const std::string& instream);
        template<typename T, int N>
        static void toHEX(const T(&arr)[N], std::string& stream);
        template<typename T, int N>
        static void fromHEX(const T(&arr)[N], const std::string& instream);
    };

    template<typename T>
    T Basic::Math::dClamp(T src, T minv, T maxv)
    {
        T t0 = dMin(minv, maxv);
        T t1 = dMax(minv, maxv);
        if (src < t0)
            src = t0;
        if (src > t1)
            src = t1;
        return src;
    }

    template<typename T>
    T Basic::Math::dScale(T src, T reference, double scale)
    {
        return reference + scale * (src - reference);
    }

    template<typename T, int N>
    void Basic::Math::fromHEX(const T(&arr)[N], const std::string& instream)
    {
        fromHEX((unsigned char*)arr, sizeof(arr), instream);
    }

    template<typename T, int N>
    void Basic::Math::toHEX(const T(&arr)[N], std::string& stream)
    {
        toHEX((unsigned char*)arr, sizeof(arr), stream);
    }

}
#endif // Math_h__
