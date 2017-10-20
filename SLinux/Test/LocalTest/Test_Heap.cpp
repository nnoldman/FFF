#include "stdafx.h"
#include "Installer.h"
#include <algorithm>
#include <list>

bool compare(int a, int b)
{
	return a < b;
	//if (a > b)
	//	return -1;
	//if (a < b)
	//	return 1;
	//return 0;
}

Function(test_heap)
{
	std::cout << std::endl;

	std::vector<int> intvec = {1,3,5,7,9,11,13};
	std::make_heap(intvec.begin(), intvec.end(), compare);

	for (auto it : intvec)
		std::cout << it << " ";
	std::cout << std::endl;

	intvec.push_back(4);
	std::push_heap(intvec.begin(), intvec.end(), compare);

	for (auto it : intvec)
		std::cout << it << " ";
	std::cout << std::endl;

	std::pop_heap(intvec.begin(), intvec.end(), compare);
	intvec.pop_back();

	for (auto it : intvec)
		std::cout << it << " ";
	std::cout << std::endl;

	std::sort_heap(intvec.begin(), intvec.end(), compare);
	for (auto it : intvec)
		std::cout << it << " ";
	std::cout << std::endl;
} 