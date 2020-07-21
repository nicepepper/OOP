#define BOOST_TEST_MODULE ArraySumTests
#include "../ArraySum/ArraySum.cpp"
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(ArraySumTests)

	BOOST_AUTO_TEST_CASE(AccumulateIntegers)
	{
		std::vector<int> vec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		BOOST_CHECK_EQUAL(ArraySum(vec), 55);
	}

	BOOST_AUTO_TEST_CASE(AccumulateStrings)
	{
		std::vector<std::string> vec = { "R", "R", "R" };
		BOOST_CHECK_EQUAL(ArraySum(vec), "RRR");
	}

	BOOST_AUTO_TEST_CASE(AccumulateFloats)
	{
		std::vector<float> vec = { 1.11f, 2.22f, 3.33f, 4.44f };
		BOOST_TEST(ArraySum(vec) == 11.1f, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(AccumulateDoubles)
	{
		std::vector<double> vec = { 1, 2, 3, 4, 5 };
		BOOST_TEST(ArraySum(vec) == 15.00f, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(AccumulateEmptyVecOfIntegers)
	{
		std::vector<int> vec;
		BOOST_CHECK_EQUAL(ArraySum(vec), 0);
	}

	BOOST_AUTO_TEST_CASE(AccumulateEmptyVecOfStrings)
	{
		std::vector<std::string> vec;
		BOOST_CHECK_EQUAL(ArraySum(vec), "");
	}

	BOOST_AUTO_TEST_CASE(AccumulateEmptyVecOfFloats)
	{
		std::vector<float> vec;
		BOOST_TEST(ArraySum(vec) == 0.00f, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(AccumulateEmptyVecOfDoubles)
	{
		std::vector<double> vec;
		BOOST_TEST(ArraySum(vec) == 0.00f, tt::tolerance(0.001));
	}

BOOST_AUTO_TEST_SUITE_END()
