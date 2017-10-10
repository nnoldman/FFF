#pragma once
#include <memory>
template<typename T>
class Ptr : public std::auto_ptr<T>
{
};


