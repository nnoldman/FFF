#ifndef IDGenerator_h__
#define IDGenerator_h__
#include <set>
namespace Basic
{
    class IDGenerator
    {
    public:
        bool add(int id);
        bool remove(int id);
        int require();
        bool query(int id);
    private:
        std::set<int> ids_;
    };
}

#endif // IDGenerator_h__
