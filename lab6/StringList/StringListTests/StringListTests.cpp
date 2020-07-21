#define BOOST_TEST_MODULE CListStringTests
#include <boost/test/unit_test.hpp>
#include "../StringList/CStringList.h"
#include <numeric>

std::string Accumulate(const CStringList& list)
{
	return std::accumulate(list.cbegin(), list.cend(), std::string());
}

BOOST_AUTO_TEST_SUITE(PushAndCheckListParamsTests)

	BOOST_AUTO_TEST_CASE(CreateListAndCheckItParams)
	{
		CStringList list;
		BOOST_CHECK_EQUAL(list.Size(), 0);
		BOOST_CHECK_EQUAL(list.IsEmpty(), true);
	}

	BOOST_AUTO_TEST_CASE(PushThenCheckListParams)
	{
		CStringList list;
		list.PushBack("A");
		BOOST_CHECK_EQUAL(list.Size(), 1);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
	}

	BOOST_AUTO_TEST_CASE(PushTripleThenCheckListParams)
	{
		CStringList list;
		list.PushBack("1");
		list.PushBack("2");
		list.PushBack("3");
		BOOST_CHECK_EQUAL(list.Size(), 3);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(InitializerListTests)

	BOOST_AUTO_TEST_CASE(CreateListAndCheckItParams)
	{
		CStringList list = { "1", "2", "3" };
		BOOST_CHECK_EQUAL(list.Size(), 3);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
	}

	BOOST_AUTO_TEST_CASE(CreateEmptyListAndCheckItParams)
	{
		CStringList list = {};
		BOOST_CHECK_EQUAL(list.Size(), 0);
		BOOST_CHECK_EQUAL(list.IsEmpty(), true);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ClearMethodTests)

	BOOST_AUTO_TEST_CASE(CreateListThenMakeItEmpty)
	{
		CStringList list = { "1", "2", "3"};
		BOOST_CHECK_EQUAL(list.Size(), 3);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		list.Clear();
		BOOST_CHECK_EQUAL(list.Size(), 0);
		BOOST_CHECK_EQUAL(list.IsEmpty(), true);
	}

	BOOST_AUTO_TEST_CASE(ClearEmptyList)
	{
		CStringList list = {};
		BOOST_CHECK_EQUAL(list.Size(), 0);
		BOOST_CHECK_EQUAL(list.IsEmpty(), true);
		list.Clear();
		BOOST_CHECK_EQUAL(list.Size(), 0);
		BOOST_CHECK_EQUAL(list.IsEmpty(), true);
	}

	BOOST_AUTO_TEST_CASE(CreateListThenMakeItEmptyAndFillItAgain)
	{
		CStringList list = { "1", "2", "3" };
		BOOST_CHECK_EQUAL(list.Size(), 3);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		list.Clear();
		BOOST_CHECK_EQUAL(list.Size(), 0);
		BOOST_CHECK_EQUAL(list.IsEmpty(), true);
		list.PushBack("5");
		list.PushBack("4");
		list.PushBack("3");
		list.PushBack("2");
		list.PushBack("1");
		BOOST_CHECK_EQUAL(Accumulate(list), "54321");
		BOOST_CHECK_EQUAL(list.Size(), 5);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IteratorsTests)

	BOOST_AUTO_TEST_CASE(CreateListAndIterateItRangeBasedFor)
	{
		CStringList list = { "1", "2", "3" };
		const std::string result = "123";
		std::string container;
		for (auto& str : list)
		{
			container += str;
		}
		BOOST_CHECK_EQUAL(container, result);
	}

	BOOST_AUTO_TEST_CASE(CreateListAndIterateItByIncIteratorFromLeft)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		const std::string result = "12345";
		std::string container;
		for (auto i = list.begin(); i != list.end(); ++i)
		{
			container += *i;
		}
		BOOST_CHECK_EQUAL(container, result);
	}

	BOOST_AUTO_TEST_CASE(CreateListAndIterateItByIncIteratorFromRight)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		const std::string result = "12345";
		std::string container;
		for (auto i = list.begin(); i != list.end(); i++)
		{
			container += *i;
		}
		BOOST_CHECK_EQUAL(container, result);
	}

	BOOST_AUTO_TEST_CASE(CreateListAndIterateItReverse)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		const std::string result = "54321";
		std::string container;
		for (auto i = list.rbegin(); i != list.rend(); ++i)
		{
			container += *i;
		}
		BOOST_CHECK_EQUAL(container, result);
	}

	BOOST_AUTO_TEST_CASE(CreateListAndReverseItByDecrementIterator)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		const std::string result = "5432";
		std::string container;
		for (auto i = --list.end(); i != list.begin(); --i)
		{
			container += *i;
		}
		BOOST_CHECK_EQUAL(container, result);
	}

	BOOST_AUTO_TEST_CASE(CreateListAndAccumulateRangeBasedFor)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		const std::string result = "12345";
		std::string container;
		for (auto& str : list)
		{
			container += str;
		}
		BOOST_CHECK_EQUAL(container, result);
	}

	BOOST_AUTO_TEST_CASE(EmptyListIteratorThrowsWhenIncrementingNullValues)
	{
		CStringList list = {};

		BOOST_CHECK_THROW(++list.begin(), std::runtime_error);
		BOOST_CHECK_THROW(--list.begin(), std::runtime_error);
		BOOST_CHECK_THROW(list.begin()++, std::runtime_error);
		BOOST_CHECK_THROW(list.begin()--, std::runtime_error);

		BOOST_CHECK_THROW(++list.end(), std::runtime_error);
		BOOST_CHECK_THROW(--list.end(), std::runtime_error);
		BOOST_CHECK_THROW(list.end()++, std::runtime_error);
		BOOST_CHECK_THROW(list.end()--, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(NotEmptyListIteratorThrowsWhenIncrementingNullValues)
	{
		CStringList list = { "R", "r" };

		BOOST_CHECK_NO_THROW(++list.begin());
		BOOST_CHECK_NO_THROW(list.begin()++);
		BOOST_CHECK_NO_THROW(--list.end());
		BOOST_CHECK_NO_THROW(list.end()--);

		BOOST_CHECK_THROW(--list.begin(), std::runtime_error);
		BOOST_CHECK_THROW(list.begin()--, std::runtime_error);
		BOOST_CHECK_THROW(++list.end(), std::runtime_error);
		BOOST_CHECK_THROW(list.end()++, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(EmptyListReverseIteratorThrowsWhenIncrementingNullValues)
	{
		CStringList list = {};

		BOOST_CHECK_THROW(++list.rbegin(), std::runtime_error);
		BOOST_CHECK_THROW(--list.rbegin(), std::runtime_error);
		BOOST_CHECK_THROW(list.rbegin()++, std::runtime_error);
		BOOST_CHECK_THROW(list.rbegin()--, std::runtime_error);

		BOOST_CHECK_THROW(++list.rend(), std::runtime_error);
		BOOST_CHECK_THROW(--list.rend(), std::runtime_error);
		BOOST_CHECK_THROW(list.rend()++, std::runtime_error);
		BOOST_CHECK_THROW(list.rend()--, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(NotEmptyListReverseIteratorThrowsWhenIncrementingNullValues)
	{
		CStringList list = { "R", "r" };

		BOOST_CHECK_NO_THROW(++list.rbegin());
		BOOST_CHECK_NO_THROW(list.rbegin()++);
		BOOST_CHECK_NO_THROW(--list.end());
		BOOST_CHECK_NO_THROW(list.end()--);

		BOOST_CHECK_THROW(--list.rbegin(), std::runtime_error);
		BOOST_CHECK_THROW(list.rbegin()--, std::runtime_error);
		BOOST_CHECK_THROW(++list.rend(), std::runtime_error);
		BOOST_CHECK_THROW(list.rend()++, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(IncrementAndDecrementIterAndCheckResult)
	{
		CStringList list = { "1", "2", "3" };
		BOOST_CHECK_EQUAL(*list.begin(), "1");
		BOOST_CHECK_EQUAL(*++list.begin(), "2");
		BOOST_CHECK_EQUAL(*++++list.begin(), "3");
	}

	BOOST_AUTO_TEST_CASE(RightIncrementOfIterator)
	{
		CStringList list = { "1", "2", "3" };
		auto iter = list.begin();
		BOOST_CHECK_EQUAL(*iter++, "1");
		BOOST_CHECK_EQUAL(*iter++, "2");
		BOOST_CHECK_EQUAL(*iter++, "3");
		BOOST_CHECK(iter == list.end());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(InsertMethodTests)

	BOOST_AUTO_TEST_CASE(InsertToBegin)
	{
		CStringList list = { "1", "2", "3" };
		list.Insert(list.begin(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(Accumulate(list), "R123");
	}

	BOOST_AUTO_TEST_CASE(InsertToBeginPlusPlus)
	{
		CStringList list = { "1", "2", "3" };
		list.Insert(++list.begin(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(Accumulate(list), "1R23");
	}

	BOOST_AUTO_TEST_CASE(InsertToEnd)
	{
		CStringList list = { "1", "2", "3" };
		list.Insert(list.end(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(Accumulate(list), "123R");
	}

	BOOST_AUTO_TEST_CASE(InsertToEndMinusMinus)
	{
		CStringList list = { "1", "2", "3" };
		list.Insert(--list.end(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(Accumulate(list), "12R3");
	}

	BOOST_AUTO_TEST_CASE(InsertToRbegin)
	{
		CStringList list = { "1", "2", "3" };
		list.Insert(list.rbegin(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(Accumulate(list), "12R3");
	}

	BOOST_AUTO_TEST_CASE(InsertToRend)
	{
		CStringList list = { "1", "2", "3" };
		list.Insert(list.rend(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(Accumulate(list), "R123");
	}

	BOOST_AUTO_TEST_CASE(InsertToEmptyContainerWithRend)
	{
		CStringList list = {};
		list.Insert(list.rend(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 1);
		BOOST_CHECK_EQUAL(Accumulate(list), "R");
	}

	BOOST_AUTO_TEST_CASE(InsertToEmptyContainerWithRbegin)
	{
		CStringList list = {};
		list.Insert(list.rbegin(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 1);
		BOOST_CHECK_EQUAL(Accumulate(list), "R");
	}

	BOOST_AUTO_TEST_CASE(InsertToEmptyContainerWithBegin)
	{
		CStringList list = {};
		list.Insert(list.begin(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 1);
		BOOST_CHECK_EQUAL(Accumulate(list), "R");
	}

	BOOST_AUTO_TEST_CASE(InsertToEmptyContainerWithEnd)
	{
		CStringList list = {};
		list.Insert(list.end(), "R");
		BOOST_CHECK_EQUAL(list.Size(), 1);
		BOOST_CHECK_EQUAL(Accumulate(list), "R");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(EraseMethodTests)

	BOOST_AUTO_TEST_CASE(EraseBegin)
	{
		CStringList list = { "1", "2", "3" };
		list.Erase(list.begin());
		BOOST_CHECK_EQUAL(list.Size(), 2);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		BOOST_CHECK_EQUAL(Accumulate(list), "23");
	}

	BOOST_AUTO_TEST_CASE(EraseEnd)
	{
		CStringList list = { "1", "2", "3" };
		BOOST_CHECK_THROW(list.Erase(list.end()), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(EraseRBegin)
	{
		CStringList list = { "1", "2", "3" };
		list.Erase(list.rbegin());
		BOOST_CHECK_EQUAL(list.Size(), 2);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		BOOST_CHECK_EQUAL(Accumulate(list), "12");
	}

	BOOST_AUTO_TEST_CASE(EraseREnd)
	{
		CStringList list = { "1", "2", "3" };
		BOOST_CHECK_THROW(list.Erase(list.rend()), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(EraseBeginPlusPlus)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		list.Erase(++++list.begin());
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		BOOST_CHECK_EQUAL(Accumulate(list), "1245");
	}

	BOOST_AUTO_TEST_CASE(EraseEndMinusMinus)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		list.Erase(----list.end());
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		BOOST_CHECK_EQUAL(Accumulate(list), "1235");
	}

	BOOST_AUTO_TEST_CASE(EraseREndMinusMinus)
	{
		CStringList list = { "1", "2", "3", "4", "5" };
		list.Erase(----list.rend());
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		BOOST_CHECK_EQUAL(Accumulate(list), "1345");
	}

	BOOST_AUTO_TEST_CASE(EraseRBeginMinusMinus)
	{
		CStringList list = { "1", "2", "3" , "4", "5" };
		list.Erase(++++list.rbegin());
		BOOST_CHECK_EQUAL(list.Size(), 4);
		BOOST_CHECK_EQUAL(list.IsEmpty(), false);
		BOOST_CHECK_EQUAL(Accumulate(list), "1245");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PushAndCheckWhatInsideTests)

	BOOST_AUTO_TEST_CASE(PushBack12345)
	{
		CStringList list;
		list.PushBack("1");
		list.PushBack("2");
		list.PushBack("3");
		BOOST_CHECK_EQUAL(list.Size(), 3);
		BOOST_CHECK_EQUAL(Accumulate(list), "123");
	}

	BOOST_AUTO_TEST_CASE(PushFront12345)
	{
		CStringList list;
		list.PushFront("1");
		list.PushFront("2");
		list.PushFront("3");
		BOOST_CHECK_EQUAL(list.Size(), 3);
		BOOST_CHECK_EQUAL(Accumulate(list), "321");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ConstIteratorsTests)

	BOOST_AUTO_TEST_CASE(AccumulateConstList)
	{
		const CStringList list = { "1", "2", "3", "4", "5" };
		BOOST_CHECK_EQUAL(list.Size(), 5);
		std::string result;
		for (auto i = list.cbegin(); i != list.cend(); ++i)
		{
			result += *i;
		}
		BOOST_CHECK_EQUAL(result, "12345");
	}

	BOOST_AUTO_TEST_CASE(AccumulateConstListReverse)
	{
		const CStringList list = { "1", "2", "3", "4", "5" };
		BOOST_CHECK_EQUAL(list.Size(), 5);
		std::string result;
		for (auto i = list.crbegin(); i != list.crend(); ++i)
		{
			result += *i;
		}
		BOOST_CHECK_EQUAL(result, "54321");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetValueFromIteratorTests)

	BOOST_AUTO_TEST_CASE(GetValueFromEmptyList)
	{
		CStringList list;

		BOOST_CHECK_THROW(*list.begin(), std::runtime_error);
		BOOST_CHECK_THROW(*list.rbegin(), std::runtime_error);
		BOOST_CHECK_THROW(*list.end(), std::runtime_error);
		BOOST_CHECK_THROW(*list.rend(), std::runtime_error);

		BOOST_CHECK_THROW(*list.cbegin(), std::runtime_error);
		BOOST_CHECK_THROW(*list.crbegin(), std::runtime_error);
		BOOST_CHECK_THROW(*list.cend(), std::runtime_error);
		BOOST_CHECK_THROW(*list.crend(), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(AssignToIterator)
	{
		CStringList list = { "A" };
		*list.begin() = "B";

		BOOST_CHECK_EQUAL(Accumulate(list), "B");
	}

	BOOST_AUTO_TEST_CASE(AssignToRbeginIterator)
	{
		CStringList list = { "a", "b" };
		*list.rbegin() = "b";
		BOOST_CHECK_EQUAL(Accumulate(list), "ab");
	}

	BOOST_AUTO_TEST_CASE(CannotAssignToEnd)
	{
		CStringList list = { "a", "a" };
		BOOST_CHECK_THROW(*list.end() = "b", std::runtime_error);
		BOOST_CHECK_EQUAL(Accumulate(list), "aa");
	}

	BOOST_AUTO_TEST_CASE(CannotAssignToREnd)
	{
		CStringList list = { "a", "a" };
		BOOST_CHECK_THROW(*list.rend() = "b", std::runtime_error);
		BOOST_CHECK_EQUAL(Accumulate(list), "aa");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SupportStlAlogirtms)

	BOOST_AUTO_TEST_CASE(MinString)
	{
		CStringList list = { "AAA", "ABA", "ABC", "cab", "aaa" };
		auto str = *std::min_element(list.begin(), list.end());
		BOOST_CHECK_EQUAL(str, "AAA");
	}

	BOOST_AUTO_TEST_CASE(MaxString)
	{
		CStringList list = { "AAA", "ABA", "ABC", "cab", "aaa" };
		auto str = *std::max_element(list.begin(), list.end());
		BOOST_CHECK_EQUAL(str, "cab");
	}

BOOST_AUTO_TEST_SUITE_END()