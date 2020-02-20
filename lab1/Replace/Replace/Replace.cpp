// Replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ReplaceSubstringsInTextFile.h"
#include "InputParams.h"
#include <iostream>

const std::string INVALID_PARAMS_MESSAGE = "Input params are invalid";

int main(int argc, char* argv[])
{
	auto params = ParseCommandLine(argc, argv);

	if (params)
	{
		std::ifstream input(params->inputFileName);
		std::ofstream output(params->outputFileName, std::ios::out | std::ios::trunc);

		if (input.is_open() && output.is_open())
		{
			ReplaceSubstringsInTextFile(input, output, params->searchString, params->replaceString);
		}

		if (!output.flush())
		{
			std::cout << "Failed to write data to output file!" << std::endl;
		}

		return 0;
	}
	else
	{
		std::cout << INVALID_PARAMS_MESSAGE << std::endl;
	}

	return 1;
}