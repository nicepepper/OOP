#include "ConversionOfStringsAndNumbers.h"

TypeInteger StringToInt(const std::string& value, const TypeInteger& radix, bool& wasError, const std::vector<char>& alphabet)
{
	constexpr char minusSign = '-';
	TypeInteger result(0);
	assert(is—orrectValue(value, radix, alphabet));
	TypeInteger digit(0);
	wasError = false;
	if (value[0] != minusSign)
	{
		for (int i = value.size() - 1, degree—ounter = 0; i >= 0; --i, ++degree—ounter)
		{
			digit = (TypeInteger)std::distance(alphabet.begin(), std::find(alphabet.begin(), alphabet.end(), value.at(i)));
			if ((MAX_INTEGER - digit * pow(radix, degree—ounter)) >= result)
			{
				result += digit * (TypeInteger)pow(radix, degree—ounter);
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
		for (size_t i = value.size() - 1, degree—ounter = 0; i > 0; --i, ++degree—ounter)
		{
			digit = (TypeInteger)std::distance(alphabet.begin(), std::find(alphabet.begin(), alphabet.end(), value.at(i)));

			if ((MIN_INTEGER + digit * pow(radix, degree—ounter)) <= result)
			{
				result -= digit * (TypeInteger)pow(radix, degree—ounter);
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

std::string IntToString(TypeInteger number, const TypeInteger& radix, bool& wasError, const std::vector<char>& alphabet)
{
	std::string str;
	std::string lineToFlip;
	char symbol;
	TypeInteger currentNumber(0);
	if (number < 0)
	{
		str.push_back('-');
	}
	while (number != 0)
	{
		symbol = alphabet[abs(number % radix)];
		number /= radix;
		lineToFlip.push_back(symbol);
	}
	while (!lineToFlip.empty())
	{
		str.push_back(lineToFlip.back());
		lineToFlip.pop_back();
	}
	return str;
}
