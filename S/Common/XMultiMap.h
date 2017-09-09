#ifndef XMultiMap_h__
#define XMultiMap_h__
#include <map>
template<typename KEY1,typename KEY2,typename VALUE>
class CXMultimap:public std::multimap<KEY1,KEY2,VALUE>
{
public:
	CXMultimap(void);
	~CXMultimap(void);
};
#endif // XMultiMap_h__
