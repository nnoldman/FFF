#pragma once
#include <map>
template<typename TK, typename TV>
class Map : public std::map<TK, TV> {
  public:
    typedef std::map<TK, TV> Super;
    typedef typename Super::iterator iterator;
    bool findkey(TK k) const {
        return this->find(k) != this->end();
    }
    bool Get(TK k, TV& v) const {
        Super::const_iterator i = find(k);

        if (i != end()) {
            v = i->second;
            return true;
        }

        return false;
    }
    bool Insert(TK k, TV v) {
        std::pair<Super::iterator, bool> res = this->insert(std::make_pair(k, v));
        return res.second;
    }
    void destroySecond(TK k) {
        Super::const_iterator i = this->find(k);

        if (i != this->end()) {
            TV p = i->second;
            dSafeDelete(p);
            this->erase(i);
        }
    }
    void destroySecond() {
        iterator i(this->begin()), iEnd(this->end());

        for (; i != iEnd; ++i) {
            dSafeDelete(i->second);
        }

        clear();
    }
};


