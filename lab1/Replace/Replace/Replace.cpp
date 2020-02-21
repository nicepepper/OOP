// Replace.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//
#include "CopyFileWithReplace.h"
#include "InputParams.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (auto params = ParseArgs(argc, argv))
	{
		std::ifstream input(params->inputFileName);
		std::ofstream output(params->outputFileName, std::ios::out | std::ios::trunc);

		if (!input.is_open())
		{
			std::cout << "Failed to open '" << params->inputFileName << "' for writing\n";
			return 1;
		}

		if (!output.is_open())
		{
			std::cout << "Failed to open '" << params->outputFileName << "' for writing\n";
			return 1;
		}

		CopyFileWithReplace(input, output, params->searchString, params->replaceString);

		if (input.bad())
		{
			std::cout << "Faild to read data from input file\n";
			return 1;
		}

		if (!output.flush())
		{
			std::cout << "Failed to write data to output file!" << std::endl;
			return 1;
		}

		return 0;
	}
	else
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}
}
