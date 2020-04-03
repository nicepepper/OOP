#include "GPN.h"
#include <iostream>
#include <string>

bool ReadNumberFromString(const std::string& number, unsigned int& num)
{
	try
	{
		num = std::stoul(number, nullptr, 0);

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Please, pass the number as the first command line param" << std::endl;
		return 1;
	}

	unsigned int num = 0;

	if (ReadNumberFromString(argv[1], num))
	{
		auto nums = GeneratePrimeNumbersSet(num);

		for (auto num : nums)
		{
			std::cout << num << std::endl;
		}
	}

	return 0;
}
