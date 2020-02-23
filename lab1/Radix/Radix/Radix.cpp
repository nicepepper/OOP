// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "InputParams.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

using namespace std;

typedef short TypeInteger;
const short MAX_INTEGER = SHRT_MAX; // todo почему то так и не смог завязать псевдонимы для MIN и MAX типа данных, пробовал tipedef и #define
const short MIN_INTEGER = SHRT_MIN;

bool isNumberInString(const string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str.at(i)))
		{
			return false;
		}
	}
	return true;
}

bool isNumberInRange(const string& str, int& number)
{
	if (isNumberInString(str))
	{
		number = atoi(str.c_str());
		if ((number >= 2) && (number <= 36))
		{
			return true;
		}
	}
	return false;
}

bool isСorrectValue(const string value, const int sourceNotation, const vector<char>& alphabet)
{
	size_t position(0);
	bool found(false);
	bool isNegativeNumber(false);

	for (size_t i = 0; i < value.size(); i++)
	{
		found = false;
		vector<char>::const_iterator result = find(alphabet.begin(), alphabet.end(), value.at(i));
		if (result != alphabet.end())
		{
			position = distance(alphabet.begin(), result);
			found = true;
		}
		if (position == 36)
		{
			if (isNegativeNumber)
			{
				return false;
			}
			isNegativeNumber = true;
		}
		if (!found || ((position != 36) && (position + 1 > sourceNotation)))
		{
			return false;
		}
	}
	return true;
}

bool isNegativeNumber(const string& value, const vector<char>& alphabet)
{
	vector<char>::const_iterator result = find(alphabet.begin(), alphabet.end(), value.at(0));
	if (distance(alphabet.begin(), result) == 36)
	{
		return true;
	}
	return false;
}

TypeInteger StringToInt(const string& value, const TypeInteger& radix, bool& wasError, const vector<char>& alphabet)
{
	TypeInteger result(0);
	assert(isСorrectValue(value, radix, alphabet));
	TypeInteger digit(0);
	wasError = false;

	if (!isNegativeNumber(value, alphabet))
	{
		for (int i = value.size() - 1, degreeСounter = 0; i >= 0; --i, ++degreeСounter)
		{
			digit = (TypeInteger)distance(alphabet.begin(), find(alphabet.begin(), alphabet.end(), value.at(i)));

			if ((MAX_INTEGER - digit * pow(radix, degreeСounter)) >= result)
			{
				result += digit * (TypeInteger)pow(radix, degreeСounter);
			}
			else
			{
				wasError = true;
				return 0;
			}
		}
	}
	else
	{
		for (size_t i = value.size() - 1, degreeСounter = 0; i > 0; --i, ++degreeСounter)
		{
			digit = (TypeInteger)distance(alphabet.begin(), find(alphabet.begin(), alphabet.end(), value.at(i)));

			if ((MIN_INTEGER + digit * pow(radix, degreeСounter)) <= result)
			{
				result -= digit * (TypeInteger)pow(radix, degreeСounter);
			}
			else
			{
				wasError = true;
				return 0;
			}
		}
	}

	return result;
}

//string IntToString(TypeInteger number, TypeInteger radix, bool& wasError, const vector<char>& alphabet)
//{
//	string str;
//
//
//
//	return str;
//}

/*
	ЭТО ВСЕ РАЗРАБОКА ДО ОСНОВНОЙ ПРОГРАММЫ
*/

// line feed to decimal notation
//cout << "max-short: " << MIN_INTEGER << endl;
//int value(0), a(0); //a - cистема cчисления, value - вводимое число
//cin >> value >> a;
//short result(0);
//int degreeсounter(0);
//while (value > 0)
//{
//	if ((short)(MIN_INTEGER - (short)(value % 10) * pow(a, degreeсounter)) >= result)
//	{
//		result += (short)(value % 10) * pow(a, degreeсounter++);
//	}
//	else
//	{
//		cout << "stack overflow!" << endl;
//	}
//	if (value % 10 >= a)
//	{
//		cerr << "wrong data!";
//		return 1;
//	}
//	value /= 10;
//}
//cout << result;
//return 0;

/*
	КОНЕЦ РАЗРАБОКИ
*/

int main(int argc, char* argv[])
{

	if (auto params = ParseArgs(argc, argv))
	{
		vector<char> alphabetOfСharacters{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
			'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
			'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'-'
		};

		int sourceNotation(0);
		if (!isNumberInRange(params->source, sourceNotation))
		{
			cout << "Argument <source notation> is set incorrectly, specify a number in the range from 2 to 36 " << endl;
			return 1;
		}

		int destinationNotation(0);
		if (!isNumberInRange(params->destination, destinationNotation))
		{
			cout << "Argument <destination notation> is set incorrectly, specify a number in the range from 2 to 36 " << endl;
			return 1;
		}

		if (!isСorrectValue(params->value, sourceNotation, alphabetOfСharacters))
		{
			cout << "This number is not correct.\n"
				 << "It contains characters that are invalid for the number system!" << endl;
			return 1;
		}

		bool wasError = false;
		TypeInteger result = StringToInt(params->value, sourceNotation, wasError, alphabetOfСharacters);
		if (wasError)
		{
			cout << "Integer overflow!\n"
				 << "Incorrect value " << endl;
			return 1;
		}
		else
		{
			cout << result << endl;
		}


		return 0;
	}
	else
	{
		cout << "Enter the parameters correctly. Do not forget they should not be empty.\n"
			 << "Usage : radix.exe <source record> <target record> <value>" << endl;
		return 1;
	}
}
