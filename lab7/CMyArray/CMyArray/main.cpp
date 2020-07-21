#include <iostream>
#include "CMyArray.h"

int main()
{
	CMyArray<int> arr = { 0, 1, 2, 3, 4, 5 };
	for (auto i = arr.begin(); i < arr.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	return 0;
}