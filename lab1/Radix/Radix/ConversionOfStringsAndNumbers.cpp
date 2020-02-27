#include "ConversionOfStringsAndNumbers.h"

TypeInteger StringToInt(const std::string& value, const TypeInteger& radix, bool& wasError)
{
	constexpr int minimalNumberSystem = 2;
	constexpr int maximumNumberSystem = 36;
	constexpr char minusSign = '-';
	wasError = false;

	if (value == "")
	{
		wasError = true;
		return 0;
	}

	if (minimalNumberSystem > radix && radix > maximumNumberSystem)
	{
		wasError = true;
		return 0;
	}
	TypeInteger result(0);
	assert(IsCorrectValue(value, radix));
	TypeInteger digit(0);
	wasError = false;
	if (value[0] != minusSign)
	{
		for (ptrdiff_t i = value.size() - 1, degree—ounter = 0; i >= 0; --i, ++degree—ounter)
		{
			digit = (TypeInteger)std::distance(alphabetOf—haracters.begin(), std::find(alphabetOf—haracters.begin(), alphabetOf—haracters.end(), value.at(i)));
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
			digit = (TypeInteger)std::distance(alphabetOf—haracters.begin(), std::find(alphabetOf—haracters.begin(), alphabetOf—haracters.end(), value.at(i)));

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

std::string IntToString(TypeInteger number, const TypeInteger& radix, bool& wasError)
{
	if (number == 0)
	{
		return "0";
	}
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
		symbol = alphabetOf—haracters[abs(number % radix)];
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
