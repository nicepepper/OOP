// Labyrinth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ParseCommandLine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	auto params = ParseComandLine(argc, argv);
	if (!params)
	{
			std::cout << "Enter the parameters correctly. Do not forget they should not be empty.\n"
					  << "Usage : Labyrinth.exe <input file> <output file>" << std::endl;
			return 1;
	}
	
	auto labyrinth = InitializeLabyrinth(params->inputFileName);

	if (!labyrinth)
	{
		std::cout << "An error has been found while initializing labyrinth\n";
		return 1;
	}

	if (FindTheWayFromLabyrinth(*labyrinth))
	{
		if (PrintLabyrinthIntoFile(params->outputFileName, *labyrinth))
		{
			return 0;
		}
		else
		{
			std::cout << "Output file error\n";
			return 1;
		}
	}
	else
	{
		std::cout << "It is impossible to exit the labyrinth\n";
		return 1;
	}

}
