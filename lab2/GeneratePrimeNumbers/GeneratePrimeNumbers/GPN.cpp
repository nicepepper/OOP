#include "GPN.h"
#include <vector>

constexpr unsigned int MAX_UPPER_BOUND = 100000000;

std::vector<bool> GenerateVectorOfPrimes(unsigned int upperBound)
{
	std::vector<bool> prime(1 + upperBound, true);

	prime[0] = prime[1] = false;

	for (unsigned int i = 2; i * i <= upperBound; ++i)
	{
		if (prime[i])
		{
			for (unsigned int j = i + i; j <= upperBound; j += i)
			{
				prime[j] = false;
			}
		}
	}

	return prime;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	std::set<int> set;

	if ((upperBound <= 0) || (upperBound > MAX_UPPER_BOUND))
	{
		return set;
	}

	auto prime = GenerateVectorOfPrimes(upperBound);

	for (int i = 0; i < int(prime.size()); i++)
	{
		if (prime[i])
		{
			set.insert(i);
		}
	}

	return set;
}