// Rle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ParseComandLine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	auto params = ParseComandLine(argc, argv);
	if (params)
	{
		//decode + decode
		std::cout << "ok paramss" << std::endl;
	}
	else
	{
		std::cout << "Enter the parameters correctly. Do not forget they should not be empty.\n"
				  << "Usage : rle.exe pack <input file> <output file>\n"
				  << "or\n"
				  << "rle.exe unpack <input file> <output file> " << std::endl;
		return 1;
	}
	return 0;
}
