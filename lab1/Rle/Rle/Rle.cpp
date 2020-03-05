// Rle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ParseComandLine.h"
#include "RLEFunctions.h"
#include <iostream>

// ? 255 - это символ конца строки

void DataCompressionAlgorithmRLE(const ProgramParameters& params)
{
	if (params.mode == pack)
	{
		if (!IsSuccessfulEcoding(params.inputFileName, params.outputFileName))
		{
			std::cout << "An error has happened encoding file" << std::endl;
		}
	}
	else
	{
		if (!IsSuccessfulDecoding(params.inputFileName, params.outputFileName))
		{
			std::cerr << "An error has happened dencoding file" << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	auto params = ParseComandLine(argc, argv);
	if (params)
	{
		DataCompressionAlgorithmRLE(*params);
	}
	else
	{
		std::cout << "Enter the parameters correctly. Do not forget they should not be empty.\n"
				  << "Usage : Rle.exe pack <input file> <output file>\n"
				  << "        Or\n"
				  << "        Rle.exe unpack <input file> <output file> " << std::endl;
		return 1;
	}
	return 0;
}
