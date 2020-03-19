#include "..\ProcessVector\ProcessVector\VectorProcessor.h"
#include <catch.hpp>
#include <vector>

TEST_CASE("VectorProcessor function - Each element of the array must be multiplied by the minimum element of the original array")
{
	std::vector<double> v = { 1.2, -2.123, 123.2, 0.0 };
	std::vector<double> v1 = { -2.5476, 4.50713, -261.554, -0 };
	CHECK(VectorProcessor(v) == v1);
}
