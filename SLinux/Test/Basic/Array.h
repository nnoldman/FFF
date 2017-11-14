#ifndef Array_h__
#define Array_h__
#include <vector>
#include <algorithm>
//--------------------------------------------------------------------------------------------------
namespace Basic
{
    template<typename T>
    class Array : public std::vector<T>
    {
    public:
        bool find(const T& rhs)
        {
            return this->end() != std::find(this->begin(), this->end(), rhs);
        }
        bool destroyPointer(const T& n)
        {
            auto i = std::find(this->begin(), this->end(), n);
            if (i != this->end())
            {
                delete n;
                this->erase(i);
                return true;
            }
            return false;
        }
        bool remove(const T& rhs)
        {
            auto i = std::find(this->begin(), this->end(), rhs);
            if (i != this->end())
            {
                this->erase(i);
                return true;
            }
            return false;
        }
        void insert(const T& after, const T& rhs)
        {
            auto i = std::find(this->begin(), this->end(), after);
            this->insert(i, rhs);
        }
        void destroy()
        {
            size_t cnt = this->size();
            for (size_t i = 0; i < cnt; ++i)
            {
                T& ptr = (*this)[i];
                delete ptr;
                ptr = 0;
            }
            this->clear();
        }
    };
}
#endif // Array_h__

