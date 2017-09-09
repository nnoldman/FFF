#ifndef Variable_h__
#define Variable_h__

namespace Basic
{
class Variable
{
public:
    static const char* space;
};

__declspec(selectany) const char* Variable::space = " ";

}
#endif // Variable_h__
