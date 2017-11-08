#include "stdafx.h"
#include "IDGenerator.h"
#include "Random.h"

bool Basic::IDGenerator::add(int id)
{
    return this->ids_.insert(id).second;
}

bool Basic::IDGenerator::remove(int id)
{
    return this->ids_.erase(id) > 0;
}

int Basic::IDGenerator::require()
{
    int ret = Basic::Random::getInstance().randI(10000, std::numeric_limits<int>::max());
    while (query(ret))
        ret = Basic::Random::getInstance().randI(10000, std::numeric_limits<int>::max());
    this->add(ret);
    return ret;
}

bool Basic::IDGenerator::query(int id)
{
    return this->ids_.find(id) != this->ids_.end();
}

const std::set<int>& Basic::IDGenerator::set() const
{
    return this->ids_;
}
