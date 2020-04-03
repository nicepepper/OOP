#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch2/catch.hpp"

#include "GeneratePrimeNumbers/GPN.h"

TEST_CASE("GeneratePrimeNumbersSet - test case")
{
	/*auto primes = GeneratePrimeNumbersSet(100000000);
	CHECK(primes.size() == 5761455);

	primes = GeneratePrimeNumbersSet(100000001);
	CHECK(primes.size() == 0);*/

	auto primes = GeneratePrimeNumbersSet(-1);
	CHECK(primes.size() == 0);

	primes = GeneratePrimeNumbersSet(10000);
	CHECK(primes.size() == 1229);
}