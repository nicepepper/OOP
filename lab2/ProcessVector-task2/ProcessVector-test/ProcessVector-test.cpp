// ProcessVector-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch2/catch.hpp"

#include "ProcessVector/ProcessVector.h"

TEST_CASE("ProcessVector function - Each element of the array must be multiplied by the minimum element of this array")
{
	//
	std::vector<double> vector = { -1, 2, 3 };
	std::vector<double> result = { 1, -2, -3 };
	ProcessVector(vector);
	CHECK(vector == result);

	//empry
	vector.clear();
	ProcessVector(vector);
	result.clear();
	CHECK(vector == result);

	// 0
	vector = { 0, 123, 123.112 };
	result = { 0, 0, 0 };
	ProcessVector(vector);
	CHECK(vector == result);
}

TEST_CASE("ReadingFromStreamToVector fnction - read from stream to vector")
{
	//empty stream
	std::stringstream str("");
	std::vector<double> vector;
	std::vector<double> result;
	ReadingFromStreamToVector(str, vector);
	CHECK(vector == result);
}