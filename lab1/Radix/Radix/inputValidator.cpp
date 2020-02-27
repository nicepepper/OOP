#include "inputValidator.h"

bool IsNumberInString(const std::string& str)
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

bool IsNumberInRange(const std::string& str, int& number)
{
	constexpr int minimalNumberSystem = 2;
	constexpr int maximumNumberSystem = 36;	
	if (IsNumberInString(str))
	{
		number = atoi(str.c_str());
		if ((number >= minimalNumberSystem) && (number <= maximumNumberSystem))
		{
			return true;
		}
	}
	return false;
}

bool IsCorrectValue(const std::string& value, const int sourceNotation)
{
	constexpr int minusPosition = 36;
	bool found(false);
	bool isNegativeNumber(false);
	size_t position(0);
	for (size_t i = 0; i < value.size(); i++)
	{
		found = false;
		std::vector<char>::const_iterator result = std::find(alphabetOfÑharacters.begin(), alphabetOfÑharacters.end(), value.at(i));
		if (result != alphabetOfÑharacters.end())
		{
			position = std::distance(alphabetOfÑharacters.begin(), result);
			found = true;
		}
		if (position == minusPosition)
		{
			if (isNegativeNumber)
			{
				return false;
			}
			isNegativeNumber = true;
			if (value.size() == 1)
			{
				return false;
			}
		}
		if (!found || ((position != minusPosition) && (position + 1 > sourceNotation)))
		{
			return false;
		}
	}
	return true;
}
