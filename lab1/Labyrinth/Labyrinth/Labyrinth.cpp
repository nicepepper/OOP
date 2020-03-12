// Labyrinth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ParseCommandLine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (auto params = ParseComandLine(argc, argv))
	{
		std::cout << "Good parametrs\n";
		return 0;
	}
	else
	{
		std::cout << "Enter the parameters correctly. Do not forget they should not be empty.\n"
				  << "Usage : Labyrinth.exe <input file> <output file>" << std::endl;
		return 1;
	}
}
