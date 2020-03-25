#pragma once
#include "ProcessVector.h"

bool ReadingFromStreamToVector(std::istream& cin, std::vector<double>& numbers)
{
	numbers.clear();
	copy(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()), std::back_inserter(numbers));
	if (!std::cin.eof())
	{
		numbers.clear();
		return false;
	}
	return true;
}

void ProcessVector(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		auto minItem = *std::min_element(numbers.begin(), numbers.end());
		auto multiplyByMin = [minItem](double number) {
			return number * minItem;
		};
		std::transform(numbers.begin(), numbers.end(), numbers.begin(), multiplyByMin);
	}
}

void PrintVectorOfNumbers(const std::vector<double>& numbers, std::ostream& cout)
{
	if (!numbers.empty())
	{
		std::copy(numbers.begin(), numbers.end() - 1, std::ostream_iterator<double>(std::cout << std::setprecision(3) << std::fixed, ", "));
		std::cout << std::setprecision(3) << std::fixed << numbers.back() << std::endl;
	}
}
