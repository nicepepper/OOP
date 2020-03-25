// HTMLDecode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "HTMLDecodeFunction.h"

int main()
{
	std::string input;

	while (std::getline(std::cin, input))
	{
		std::cout << HTMLDecode(input) << std::endl;
	}

	return 0;
}
