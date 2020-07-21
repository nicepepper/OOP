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

BOOST_AUTO_TEST_SUITE_END()