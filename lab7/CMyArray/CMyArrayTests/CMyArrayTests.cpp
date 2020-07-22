#define BOOST_TEST_MODULE MyArrayTests
#include "../CMyArray/CMyArray.h"
#include <boost/test/unit_test.hpp>
#include <numeric>

BOOST_AUTO_TEST_SUITE(MyArrayConstructorsTests)

	BOOST_AUTO_TEST_CASE(InitEmptyArray)
	{
		const CMyArray<int> arr;
		BOOST_CHECK(arr.Size() == 0);
	}

	BOOST_AUTO_TEST_CASE(CopyConstructor)
	{
		CMyArray<std::string> arr1;
		arr1.PushBack("1");
		arr1.PushBack("2");
		arr1.PushBack("3");
		CMyArray<std::string> arr2(arr1);
		
		BOOST_CHECK_EQUAL(arr1.Size(), 3);
		BOOST_CHECK_EQUAL(arr1.Size(), arr2.Size());
		for (size_t i = 0; i < arr1.Size(); ++i)
		{
			BOOST_CHECK_EQUAL(arr1[i], arr2[i]);
		}
	}

	BOOST_AUTO_TEST_CASE(CopyAssignmentConstructor)
	{
		CMyArray<std::string> arr1;
		arr1.PushBack("1");
		arr1.PushBack("2");
		arr1.PushBack("3");
		CMyArray<std::string> arr2 = arr1;
		
		BOOST_CHECK_EQUAL(arr1.Size(), 3);
		BOOST_CHECK_EQUAL(arr1.Size(), arr2.Size());
		for (size_t i = 0; i < arr1.Size(); ++i)
		{
			BOOST_CHECK_EQUAL(arr1[i], arr2[i]);
		}
	}

	BOOST_AUTO_TEST_CASE(InitListConstructor)
	{
		CMyArray<std::string> arr = { "1", "2", "3" };
		std::string str;
		auto result = std::accumulate(arr.begin(), arr.end(), str);

		BOOST_CHECK_EQUAL(result, "123");
	}

	BOOST_AUTO_TEST_CASE(CopySelf)
	{
		CMyArray<std::string> arr;
		arr.PushBack("1");
		arr.PushBack("2");
		arr.PushBack("3");
		arr = arr;

		BOOST_CHECK_EQUAL(arr.Size(), 3);
		BOOST_CHECK_EQUAL(arr[0], "1");
		BOOST_CHECK_EQUAL(arr[1], "2");
		BOOST_CHECK_EQUAL(arr[2], "3");
	}

	BOOST_AUTO_TEST_CASE(MoveConstructor)
	{
		CMyArray<std::string> arr1;
		arr1.PushBack("1");
		arr1.PushBack("2");
		arr1.PushBack("3");

		BOOST_CHECK_EQUAL(arr1.Size(), 3);
		
		CMyArray<std::string> arr2(std::move(arr1));
		
		BOOST_CHECK_EQUAL(arr1.Size(), 0);
		BOOST_CHECK_EQUAL("1", arr2[0]);
		BOOST_CHECK_EQUAL("2", arr2[1]);
		BOOST_CHECK_EQUAL("3", arr2[2]);
		BOOST_CHECK_EQUAL(arr2.Size(), 3);
	}

	BOOST_AUTO_TEST_CASE(MoveAssignmentConstructor)
	{
		CMyArray<std::string> arr1;
		arr1.PushBack("1");
		arr1.PushBack("2");
		arr1.PushBack("3");

		BOOST_CHECK_EQUAL(arr1.Size(), 3);

		CMyArray<std::string> arr2 = std::move(arr1);

		BOOST_CHECK_EQUAL(arr1.Size(), 0);
		BOOST_CHECK_EQUAL("1", arr2[0]);
		BOOST_CHECK_EQUAL("2", arr2[1]);
		BOOST_CHECK_EQUAL("3", arr2[2]);
		BOOST_CHECK_EQUAL(arr2.Size(), 3);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PushBackMethodsTests)

	BOOST_AUTO_TEST_CASE(PushAndCheckIfExists)
	{
		CMyArray<int> arr;
		arr.PushBack(5);

		BOOST_CHECK(arr[0] == 5);
		BOOST_CHECK(arr.Size() == 1);
	}

	BOOST_AUTO_TEST_CASE(PushMultipleTimesAndCHeck)
	{
		CMyArray<int> arr;
		arr.PushBack(3);
		arr.PushBack(2);
		arr.PushBack(1);
		arr.PushBack(0);

		BOOST_CHECK(arr.Size() == 4);
		for (int i = 0; i < 4; ++i)
		{
			BOOST_CHECK(arr[i] == int(arr.Size()) - 1 - i);
		}
	}

	BOOST_AUTO_TEST_CASE(PushStringsAndConcatenateThem)
	{
		CMyArray<char> arr;
		char ch = 'a';
		std::string result;
		for (size_t i = 0; i < 26; ++i)
		{
			arr.PushBack(ch);
			ch++;
			result += arr[i];
		}

		BOOST_CHECK(arr.Size() == 26);
		BOOST_CHECK(result == "abcdefghijklmnopqrstuvwxyz");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SquareBracketsOperatorOverloading)

	BOOST_AUTO_TEST_CASE(ChangeValueOfFirstElement)
	{
		CMyArray<int> arr;
		arr.PushBack(10);
		BOOST_CHECK_EQUAL(arr[0], 10);
		arr[0] = 20;
		BOOST_CHECK_EQUAL(arr[0], 20);
	}

	BOOST_AUTO_TEST_CASE(NotThrowsWhenInRange)
	{
		CMyArray<int> arr;
		arr.PushBack(123);
		BOOST_CHECK_NO_THROW(arr[0]);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenOutOfRangeEmptyArray)
	{
		CMyArray<int> arr;
		BOOST_CHECK_THROW(arr[0], std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenOutOfRange)
	{
		CMyArray<int> arr;
		arr.PushBack(12345);
		BOOST_CHECK_THROW(arr[1], std::out_of_range);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ClearMethodsTests)

	BOOST_AUTO_TEST_CASE(ClearEmpty)
	{
		CMyArray<int> arr;
		BOOST_CHECK_EQUAL(arr.Size(), 0);
		arr.Clear();
		BOOST_CHECK_EQUAL(arr.Size(), 0);
	}

	BOOST_AUTO_TEST_CASE(ClearNotEmpty)
	{
		CMyArray<std::string> arr;
		arr.PushBack("a");
		arr.PushBack("b");
		arr.PushBack("c");
		BOOST_CHECK_EQUAL(arr.Size(), 3);
		arr.Clear();
		BOOST_CHECK_EQUAL(arr.Size(), 0);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ResizeMethodTests)

	BOOST_AUTO_TEST_CASE(ResizeEmpty)
	{
		CMyArray<int> arr;
		arr.Resize(100);
		BOOST_CHECK_EQUAL(arr.Size(), 100);
		for (size_t i = 0; i < 100; ++i)
		{
			BOOST_CHECK_EQUAL(arr[i], 0);
		}
	}

	BOOST_AUTO_TEST_CASE(ResizeToSmallerValue)
	{
		CMyArray<int> arr;
		arr.PushBack(1);
		arr.PushBack(2);
		arr.PushBack(3);
		arr.Resize(2);

		BOOST_CHECK_EQUAL(arr[0], 1);
		BOOST_CHECK_EQUAL(arr[1], 2);
		BOOST_CHECK_THROW(arr[2], std::out_of_range);
		BOOST_CHECK_EQUAL(arr.Size(), 2);
	}

	BOOST_AUTO_TEST_CASE(ResizeToBiggerValue)
	{
		CMyArray<int> arr;
		arr.PushBack(1);
		arr.PushBack(2);
		arr.PushBack(3);
		arr.Resize(5);

		BOOST_CHECK_EQUAL(arr[0], 1);
		BOOST_CHECK_EQUAL(arr[1], 2);
		BOOST_CHECK_EQUAL(arr[2], 3);
		BOOST_CHECK_EQUAL(arr[3], 0);
		BOOST_CHECK_EQUAL(arr[4], 0);
		BOOST_CHECK_EQUAL(arr.Size(), 5);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IteratorsTests)

	BOOST_AUTO_TEST_CASE(AccumulateStringsWithIterators)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		BOOST_CHECK_EQUAL(arr.Size(), 4);
		std::string result;
		for (const auto& el : arr)
		{
			result += el;
		}
		
		BOOST_CHECK_EQUAL(result, "0123");
	}

	BOOST_AUTO_TEST_CASE(AccumulateStringsWithReverseIterators)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		BOOST_CHECK_EQUAL(arr.Size(), 4);
		std::string result;
		for (auto i = arr.rbegin(); i != arr.rend(); ++i)
		{
			result += *i;
		}

		BOOST_CHECK_EQUAL(result, "3210");
	}

	BOOST_AUTO_TEST_CASE(ChangeValueThroughtIterator)
	{
		CMyArray<std::string> arr = { "1", "2", "3" };
		*arr.begin() = "6";
		*++arr.begin() = "6";
		*++++arr.begin() = "6";
		std::string result;
		for (const auto& el : arr)
		{
			result += el;
		}

		BOOST_CHECK_EQUAL(result, "666");
	}

	BOOST_AUTO_TEST_CASE(ChangeValueThroughtReverseIterator)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		*arr.rbegin() = "0";
		*++arr.rbegin() = "1";
		std::string result;
		for (const auto& el : arr)
		{
			result += el;
		}

		BOOST_CHECK_EQUAL(result, "0110");
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenGetValueThroughIteratorOfEmptyArray)
	{
		CMyArray<std::string> arr;
		BOOST_CHECK_THROW(*arr.begin(), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenGetValueThroughReverseIteratorOfEmptyArray)
	{
		CMyArray<std::string> arr;
		BOOST_CHECK_THROW(*arr.rbegin(), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenGetValueOfEndIterator)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		BOOST_CHECK_THROW(*arr.end(), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenGetValueOfReverseEndIterator)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		BOOST_CHECK_THROW(*arr.rend(), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenIncrementEndIterator)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		
		BOOST_CHECK_THROW(++arr.rend(), std::out_of_range);
		BOOST_CHECK_THROW(++arr.end(), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(ThrowsWhenDecrementBeginIterator)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		
		BOOST_CHECK_THROW(--arr.begin(), std::out_of_range);
		BOOST_CHECK_THROW(--arr.rbegin(), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(CannotCompareReverseAndUsualIterator)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
		
		BOOST_CHECK_THROW(arr.begin() < arr.rend(), std::exception);
		BOOST_CHECK_THROW(arr.begin() <= arr.rend(), std::exception);
		BOOST_CHECK_THROW(arr.begin() >= arr.rend(), std::exception);
		BOOST_CHECK_THROW(arr.rbegin() < arr.end(), std::exception);
	}

	BOOST_AUTO_TEST_CASE(ComparingIteratorsWithLessMoreOperators)
	{
		CMyArray<std::string> arr = { "0", "1", "2", "3" };
	
		BOOST_CHECK(arr.begin() < arr.end());
		BOOST_CHECK(arr.rbegin() < arr.rend());
		BOOST_CHECK(arr.rbegin() <= arr.rend());
		BOOST_CHECK(arr.end() >= arr.begin());
	}

	BOOST_AUTO_TEST_CASE(CanBeAccumulateWithSTLAlgorithm)
	{
		CMyArray<std::string> arr = { "a", "b", "c", "d" };
		std::string str;
		auto result = std::accumulate(arr.begin(), arr.end(), str);

		BOOST_CHECK_EQUAL(result, "abcd");
	}

BOOST_AUTO_TEST_SUITE_END()