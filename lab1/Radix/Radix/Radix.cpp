// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ConversionOfStringsAndNumbers.h"
#include "InputParams.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	if (auto params = ParseArgs(argc, argv))
	{
		int sourceNotation(0);
		if (!StringValueSuitableForRadix(params->source, sourceNotation))
		{
			std::cout << "Argument <source notation> is set incorrectly, specify a number in the range from 2 to 36 " << std::endl;
			return 1;
		}
		int destinationNotation(0);
		if (!StringValueSuitableForRadix(params->destination, destinationNotation))
		{
			std::cout << "Argument <destination notation> is set incorrectly, specify a number in the range from 2 to 36 " << std::endl;
			return 1;
		}
		if (!IsStringCorrectForNumberSystem(params->value, sourceNotation))
		{
			std::cout << "This value is not correct.\n"
					  << "It contains characters that are not allowed for the number system!" << std::endl;
			return 1;
		}
		bool wasError = false;
		TypeInteger result = StringToInt(params->value, sourceNotation, wasError);
		if (wasError)
		{
			std::cout << "Integer overflow!\n"
					  << "Incorrect value " << std::endl;
			return 1;
		}
		std::string strResult = IntToString(result, destinationNotation, wasError);
		if (!wasError)
		{
			std::cout << strResult << std::endl;
		}
		else
		{
			std::cout << "error translating from integer to string" << std::endl;
			return 1;
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
