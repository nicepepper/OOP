#pragma once
#include <vector>

template <class T>
T ArraySum(const std::vector<T>& vec)
{
	T sum = {};

	for (const auto& el : vec)
	{
		sum += el;
	}

	return sum;
}