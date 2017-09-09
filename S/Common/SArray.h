#ifndef SArray_h__
#define SArray_h__

namespace Basic
{
template<typename T, unsigned int N>
class SArray
{
public:
    unsigned int size()
    {
        return N;
    }
    T& operator[](unsigned int i)
    {
        CHECK(ISIN(i, 0, N));
        return elements_[i];
    }
    T& Get(unsigned int i)
    {
        CHECK(ISIN(i, 0, N));
        return elements_[i];
    }
private:
    T elements_[N];
};

}




#endif // SArray_h__
