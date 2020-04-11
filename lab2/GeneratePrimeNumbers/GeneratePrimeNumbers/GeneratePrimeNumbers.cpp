#include "GPN.h"
#include <algorithm>
#include <boost/timer.hpp>
#include <iostream>
#include <iterator>
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
		boost::timer t;
		t.restart();
		auto nums = GeneratePrimeNumbersSet(num);
		double duration = t.elapsed();
		std::cout << "The time to build a set of primes in the range from 1 to " << argv[1] << " : " << duration << "sec.\n"
				  << "Please press Enter to display prime numbers." << std::endl;
		getchar();
		std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, "\n"));
	}
	return 0;
}
