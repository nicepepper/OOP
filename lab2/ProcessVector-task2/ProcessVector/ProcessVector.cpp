#pragma once
#include "ProcessVector.h"

std::optional<std::vector<double>> ReadingFromStreamToVector(std::istream& cin, std::vector<double>& numbers)
{

	copy(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()), std::back_inserter(numbers));

	if (!std::cin.eof())
	{
		return std::nullopt;
	}

	return numbers;
}

void ProcessVector(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		auto minItemPos = std::min_element(numbers.begin(), numbers.end());

		auto minItem = numbers.at(std::distance(numbers.begin(), minItemPos));

		auto resultMultiplication = [&minItem](double number) {
			return number * minItem;
		};

		std::transform(numbers.begin(), numbers.end(), numbers.begin(), resultMultiplication);
	}
}

void PrintVectorOfNumbers(const std::vector<double>& numbers, std::ostream& cout)
{
	if (!numbers.empty())
	{
		std::copy(numbers.begin(), numbers.end() - 1, std::ostream_iterator<double>(std::cout, ", "));
		std::cout << numbers.back() << std::endl;
	}
}
