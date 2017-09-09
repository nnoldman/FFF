#include "stdafx.h"
#include "test_move.h"
#include <sstream>
class TClass
{
public:
    TClass()
    {
        id = sCount++;
        stringstream os;
        os << id;
        name = os.str();
        os >> id;
    }
    int id;
    string name;
public:
    static int sCount;
};

int TClass::sCount = 0;

vector<TClass> getVector()
{
    vector<TClass> vec;
    TClass a;
    TClass b;
    TClass c;
    TClass d;
    TClass e;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
    vec.push_back(e);
    return vec;
    //return std::move(vec);
}

test_move::test_move()
{
    vector<TClass> ret = getVector();
}


test_move::~test_move()
{
}
