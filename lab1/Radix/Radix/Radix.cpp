// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

typedef short TypeInteger;
const short MAX_INTEGER = SHRT_MAX; // todo почему то так и не смог завязать псевдонимы для MIN и MAX для типа данных, пробовал tipedef и #define
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

bool isNumberInRange(const string& str, TypeInteger number)
{
	if (isNumberInString(str))
	{
		number = atoi(str.c_str());
		if (2 <= number <= 36)
		{
			return true;
		}
	}
	return false;
}

int StringToInt(const string& str, int radix, bool& wasError)
{
}
string IntToString(int n, int radix, bool& wasError)
{
}

int main(int argc, char* argv[])
{

	/*
	ЭТО ВСЕ РАЗРАБОКА ДО ОСНОВНОЙ ПРОГРАММЫ
	*/
	//cout << "Hello World!\n";
	/*cout << "Sizeof MAXINT: " << INT_MAX << endl;

	cout << "int64 - max:" << LLONG_MAX << endl;
	cout << "int64 - min:" << LLONG_MIN << endl;

	int64_t number;

	string numberString = "23AB";
	vector<int64_t> charMassiv;*/

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

	// тут уже идет основная программа
	if (argc != 3)
	{
		std::cout << "Invalid argument count.\n"
				  << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	if (argv[1] == "" || argv[2] == "" || argv[3] == "")
	{
		cout << "Enter parameters correctly one of the arguments is empty.\n"
			 << "Usage: radix.exe <source notation> <destination notation> <value>\n";
	}

	vector<char> alphabetOfСharacters{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
		'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	// argument validation
	TypeInteger sourceNotation(0);
	TypeInteger destinationNotation(0);
	string value;
	if (isNumberInRange(argv[1], sourceNotation))
	{
		cout << "Argument <source notation> is set incorrectly, specify a number in the range from 2 to 36 ";
		return 1;
	}

	if (isNumberInRange(argv[2], destinationNotation))
	{
		cout << "Argument <destination notation> is set incorrectly, specify a number in the range from 2 to 36 ";
		return 1;
	}

	
	return 0;
}
