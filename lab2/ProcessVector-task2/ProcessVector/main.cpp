// ProcessVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ProcessVector.h"

int main()
{
	std::vector<double> vectorOfNumbers;

	if (!ReadingFromStreamToVector(std::cin, vectorOfNumbers))
	{
		std::cout << "\nError reading from stream to vector\n";
		return 1;
	}

	ProcessVector(vectorOfNumbers);

	std::sort(vectorOfNumbers.begin(), vectorOfNumbers.end());
	PrintVectorOfNumbers(vectorOfNumbers, std::cout);
	return 0;
}
