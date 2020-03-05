#include "RLEFunctions.h"

bool IsSuccessfulEcoding(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream input(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream output(outputFileName, std::ios::binary);

	if (!input.is_open())
	{
		return false;
	}
	
	return false;
}

bool IsSuccessfulDecoding(const std::string& inputFileName, const std::string& outputFileName)
{
	return false;
}
