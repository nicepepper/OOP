#include "ConversionOfStringsAndNumbers.h"

unsigned OverflowAdd(unsigned x, unsigned y, bool& overflow, const unsigned max)
{
	overflow = x + y > static_cast<unsigned>(max);
	if (!overflow)
	{
		return x + y;
	}
	return 0;
}

unsigned OverflowMult(unsigned x, unsigned y, bool& overflow, const unsigned max)
{
	if (x != 0)
	{
		overflow = (static_cast<unsigned>(max) + 1) / x < y;
	}
	if (!overflow)
	{
		return x * y;
	}
	return 0;
}

unsigned StringToUnsignedInteger(const std::string& value, const TypeInteger& radix, bool& overflow, const unsigned max)
{
	unsigned result(0);
	unsigned digit(0);
	for (size_t i = 0; i < value.size(); i++)
	{
		digit = static_cast<unsigned>(distance(alphabetOfÑharacters.begin(), std::find(alphabetOfÑharacters.begin(), alphabetOfÑharacters.end(), value.at(i))));
		if (digit == 36)
		{
			continue;
		}

		if (!overflow)
		{
			result = OverflowMult(result, radix, overflow, max);
			if (overflow)
			{
				break;
			}
			result = OverflowAdd(result, digit, overflow, max);

			if (overflow)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	if (overflow)
	{
		return 1;
	}
	return result;
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
	if (!IsStringCorrectForNumberSystem(value, radix))
	{
		wasError = true;
		return 0;
	}

	TypeInteger result(0);
	unsigned max(0);
	if (value[0] != minusSign)
	{
		max = static_cast<unsigned>(MAX_INTEGER);
		result = static_cast<TypeInteger>(StringToUnsignedInteger(value, radix, wasError, max));
	}
	else
	{
		max = static_cast<unsigned>(MIN_INTEGER);
		result = static_cast<TypeInteger>(StringToUnsignedInteger(value, radix, wasError, max));
		result *= (-1);
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
		symbol = alphabetOfÑharacters[abs(number % radix)];
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
