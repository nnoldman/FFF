#include "stdafx.h"
#include "test_shared_pointer.h"

struct CommonStruct 
{
	int code;
	string name;
	~CommonStruct() {
	}
};
test_shared_pointer::test_shared_pointer()
{
}


test_shared_pointer::~test_shared_pointer()
{
}

void test_shared_pointer::test()
{
	std::vector<shared_ptr<CommonStruct>> csVector;
	csVector.push_back(shared_ptr<CommonStruct>(new CommonStruct()));
	shared_ptr<CommonStruct> cs = csVector.front();
	assert(cs.use_count() == 2);

	std::vector<shared_ptr<CommonStruct>>* csVector2 = new std::vector<shared_ptr<CommonStruct>>();
	*csVector2 = csVector;
	assert(cs.use_count() == 3);

	delete csVector2;
	assert(cs.use_count() == 2);
}
