// Dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DictionaryCLI.h"
#include "ParsingCommandLine.h"
#include <iostream>
#include <windows.h>

void dialogSettings()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//system("cls");
}

int main(int argc, char* argv[])
{
	dialogSettings();
	auto parametrCL = ParseComandLine(argc, argv);
	if (parametrCL)
	{
		DictionaryCLI(parametrCL->inputFileName);
		return 0;
	}
	else
	{
		std::cout << "Please, pass the name of dictionary file as the first param of command line\n"
				  << "Usage Dictionary.exe <dictionary file name>" << std::endl;
		return 1;
	}
}
