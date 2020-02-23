// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ConversionOfStringsAndNumbers.h"
#include "InputParams.h"
#include <iostream>
#include <string>
#include <vector>

// ???разрешено ли использоваить  strtol()? и подобные функции,
// ??? вопрос про константы в подключаемых файлах (extern - ifndef/ifendef и так далее что лучше)
// ??? const или все же constexpr что использовать для такого
// ??? использование constexpr в функция для локальных переменных это ведь нормально убирать таким образом "магические числа"
int main(int argc, char* argv[])
{
	if (auto params = ParseArgs(argc, argv))
	{
		int sourceNotation(0);
		if (!isNumberInRange(params->source, sourceNotation))
		{
			std::cout << "Argument <source notation> is set incorrectly, specify a number in the range from 2 to 36 " << std::endl;
			return 1;
		}

		int destinationNotation(0);
		if (!isNumberInRange(params->destination, destinationNotation))
		{
			std::cout << "Argument <destination notation> is set incorrectly, specify a number in the range from 2 to 36 " << std::endl;
			return 1;
		}

		if (!isСorrectValue(params->value, sourceNotation, alphabetOfСharacters))
		{
			std::cout << "This value is not correct.\n"
					  << "It contains characters that are not allowed for the number system!" << std::endl;
			return 1;
		}

		bool wasError = false;
		TypeInteger result = StringToInt(params->value, sourceNotation, wasError, alphabetOfСharacters);
		if (wasError)
		{
			std::cout << "Integer overflow!\n"
					  << "Incorrect value " << std::endl;
			return 1;
		}

		//нужен пример ошиьки я не могу определиться что тут может быть
		std::string strResult = IntToString(result, destinationNotation, wasError, alphabetOfСharacters);
		if (!wasError)
		{
			std::cout << strResult << std::endl;
		}
		return 0;
	}
	else
	{
		std::cout << "Enter the parameters correctly. Do not forget they should not be empty.\n"
				  << "Usage : radix.exe <source record> <target record> <value>" << std::endl;
		return 1;
	}
}
