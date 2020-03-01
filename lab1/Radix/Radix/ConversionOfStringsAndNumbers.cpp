#include "ConversionOfStringsAndNumbers.h"

unsigned OverflowAdd(unsigned x, unsigned y, bool& overflow)
{
	overflow = x + y <= static_cast<unsigned>(INT_MAX) + 1;
	return x + y;
}

unsigned OverflowMult(unsigned x, unsigned y, bool& overflow)
{
	overflow = false;
	if (x != 0)
	{
		overflow = (static_cast<unsigned>(INT_MAX) + 1) / x > y;
	}
	if (!overflow)
	{
		return x * y;
	}
	return 0;
}

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
	assert(IsStringCorrectForNumberSystem(value, radix));
	
	TypeInteger result(0);
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
	constexpr int minimalNumberSystem = 2;
	constexpr int maximumNumberSystem = 36;
	if (number == 0)
	{
		return "0";
	}
	if (minimalNumberSystem > radix && radix > maximumNumberSystem)
	{
		wasError = true;
		return 0;
	}
	bool negativeNumber(false);
	if (number < 0)
	{
		negativeNumber = true;
	}
	std::string resultStr;
	char symbol;
	while (number != 0)
	{
		symbol = alphabetOf—haracters[abs(number % radix)];
		number /= radix;
		resultStr.push_back(symbol);
	}
	reverse(resultStr.begin(), resultStr.end());
	if (negativeNumber)
	{
		resultStr = '-' + resultStr;
	}
	return resultStr;
}
