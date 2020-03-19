// ProcessVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "VectorProcessor.h"

int main()
{
	std::vector<double> vectorOfNumbers;

	if (!ReadingFromStreamToVector(std::cin, vectorOfNumbers))
	{
		std::cout << "Error reading from stream to vector\n";
		return 0;
	}

	VectorProcessor(vectorOfNumbers);

	std::sort(vectorOfNumbers.begin(), vectorOfNumbers.end());
	PrintVectorOfNumbers(vectorOfNumbers, std::cout);
	std::cout << "Size of vector: " << vectorOfNumbers.size() << "\n";
	return 0;
}
