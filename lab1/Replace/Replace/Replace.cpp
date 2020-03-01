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
		if (CopyWithReplace(params->inputFileName, params->outputFileName, params->searchString, params->replaceString))
		{
			std::cout << "Replacement string was successful" << std::endl;
			return 0;		
		}
		return 1;
	}
	else
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}
}
