// Dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ParsingCommandLine.h"

void PrintHelpInfo()
{
	std::cout << "Please, pass the name of dictionary file as the first param of command line" << std::endl;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
	auto parametrCL = ParseComandLine(argc, argv);
	if (parametrCL)
	{
		//Deictionary(parametrCL->inputFileName);
		std::cout << "OK!" << std::endl;
	}
	else
	{
		PrintHelpInfo();
	}
	return 0;
}
