#define BOOST_TEST_MODULE MyStringTests
#include "../CMyString/CMyString.h"
#include <boost/test/unit_test.hpp>
#include <iostream>

bool AreThisCStringsEqual(const char* str1, const char* str2)
{
	if (strlen(str1) != strlen(str2))
	{
		return false;
	}
	for (size_t i = 0; i < strlen(str1); i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(MyStringConstructorsTests)

	BOOST_AUTO_TEST_CASE(InitEmptyStrContainer)
	{
		CMyString str;
		BOOST_CHECK(str.GetLength() == 0);
		BOOST_CHECK(str.GetStringData() == "");
	}

	BOOST_AUTO_TEST_CASE(InitStringFromCString)
	{
		const char* strC = "Hello, world!";
		CMyString str(strC);
		BOOST_CHECK(str.GetLength() == 13);
		BOOST_CHECK(str.GetStringData() != nullptr);
		BOOST_CHECK(strcmp(str.GetStringData(), strC) == 0);
	}

	BOOST_AUTO_TEST_CASE(InitStrFromCStrWithConstLength)
	{
		const char* strC = "Hello, world!";
		const char* strResult = "Hello";
		CMyString str(strC, 5);
		BOOST_CHECK(str.GetLength() == 5);
		BOOST_CHECK(str.GetStringData() != nullptr);
		BOOST_CHECK(strcmp(str.GetStringData(), strResult) == 0);
	}

	BOOST_AUTO_TEST_CASE(InitStrFromStlString)
	{
		const std::string strS = "Hello, world!";
		CMyString str(strS);
		BOOST_CHECK(str.GetLength() == 13);
		BOOST_CHECK(strcmp(str.GetStringData(), strS.c_str()) == 0);
	}

	BOOST_AUTO_TEST_CASE(InitFromCopyConstructor)
	{
		const CMyString str("Hello, world!");
		const auto strCopy(str);
		BOOST_CHECK(strCopy.GetLength() == 13);
		BOOST_CHECK(strcmp(strCopy.GetStringData(), str.GetStringData()) == 0);
	}

	BOOST_AUTO_TEST_CASE(InitFromMoveConstructor)
	{
		const char* strReal = "Hello, world!";
		const CMyString str(CMyString("Hello, world!"));
		BOOST_CHECK(str.GetLength() == 13);
		BOOST_CHECK(strcmp(str.GetStringData(), strReal) == 0);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MyStringPlusOperator)

	BOOST_AUTO_TEST_CASE(ConcatenateTwoEmptyString)
	{
		CMyString str;
		CMyString str2;
		auto str3 = str + str2;
		BOOST_CHECK(strcmp(str3.GetStringData(), "") == 0);
	}

	BOOST_AUTO_TEST_CASE(ConcatenateHelloAndWorld)
	{
		CMyString str("Hello");
		CMyString str2("MyWorld");
		auto str3 = str + str2;
		BOOST_CHECK(strcmp(str3.GetStringData(), "HelloMyWorld") == 0);
		BOOST_CHECK(str3.GetLength() == 12);
	}

	BOOST_AUTO_TEST_CASE(ConcatenateHelloAndEmptyStr)
	{
		CMyString str("Hello");
		CMyString str2;
		auto str3 = str + str2;
		BOOST_CHECK(strcmp(str3.GetStringData(), "Hello") == 0);
		BOOST_CHECK(str3.GetLength() == 5);
	}

	BOOST_AUTO_TEST_CASE(ConcatenateEmptyStrAndHello)
	{
		CMyString str;
		CMyString str2("Hello");
		auto str3 = str + str2;
		BOOST_CHECK(strcmp(str3.GetStringData(), "Hello") == 0);
		BOOST_CHECK(str3.GetLength() == 5);
	}

	BOOST_AUTO_TEST_CASE(PlusEqualOperatorToEmptyString)
	{
		CMyString str;
		str += "Hello";
		BOOST_CHECK(strcmp(str.GetStringData(), "Hello") == 0);
		BOOST_CHECK(str.GetLength() == 5);
	}

	BOOST_AUTO_TEST_CASE(PlusEqualOperatorToItself)
	{
		CMyString str("ma");
		str += str;
		BOOST_CHECK(strcmp(str.GetStringData(), "mama") == 0);
		BOOST_CHECK(str.GetLength() == 4);
	}

	BOOST_AUTO_TEST_CASE(PlusEqualOperatorEmptyStrs)
	{
		CMyString str;
		str += str;
		BOOST_CHECK(strcmp(str.GetStringData(), "") == 0);
		BOOST_CHECK(str.GetLength() == 0);
	}

	BOOST_AUTO_TEST_CASE(PlusEqualOperatorEmprtyStrAndCharA)
	{
		CMyString str;
		str += '1';
		BOOST_CHECK(strcmp(str.GetStringData(), "1") == 0);
		BOOST_CHECK_EQUAL(str.GetStringData()[str.GetLength()], '\0');
		BOOST_CHECK(str.GetLength() == 1);
	}

	BOOST_AUTO_TEST_CASE(PlusEqualOperatorToChars)
	{
		CMyString str("glh");
		str += 'f';
		BOOST_CHECK(strcmp(str.GetStringData(), "glhf") == 0);
		BOOST_CHECK(str.GetLength() == 4);
	}

	BOOST_AUTO_TEST_CASE(PlusOperatorToChar)
	{
		CMyString str("Rashitov ");
		auto str2 = str + 'R';
		BOOST_CHECK(strcmp(str2.GetStringData(), "Rashitov R") == 0);
		BOOST_CHECK(str2.GetLength() == 10);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(StreamOperatorsTests)

	BOOST_AUTO_TEST_CASE(ReadStrFromStream)
	{
		CMyString str;
		std::istringstream stream(" Hello, world!");
		stream >> str;
		BOOST_CHECK(str.GetLength() == 6);
		BOOST_CHECK(strcmp(str.GetStringData(), "Hello,") == 0);
	}

	BOOST_AUTO_TEST_CASE(PrintStrToStream)
	{
		CMyString str("Hello");
		std::ostringstream stream;
		stream << str;
		BOOST_CHECK(strcmp(stream.str().c_str(), "Hello") == 0);
	}

	BOOST_AUTO_TEST_CASE(PrintStrToStreamEmptyStr)
	{
		CMyString str("");
		std::ostringstream stream;
		stream << str;
		BOOST_CHECK(strcmp(stream.str().c_str(), "") == 0);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SquareBracketsOperatorTests)

	BOOST_AUTO_TEST_CASE(AccessToStrValuesInGoodRange)
	{
		const CMyString str("12345");
		BOOST_CHECK(str[0] == '1');
		BOOST_CHECK(str[1] == '2');
		BOOST_CHECK(str[2] == '3');
		BOOST_CHECK(str[3] == '4');
		BOOST_CHECK(str[4] == '5');
	}

	BOOST_AUTO_TEST_CASE(AccessToStrValuesOutOfRange)
	{
		const CMyString str("12345");
		BOOST_CHECK_THROW(str[5], std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(AccessToEmptyStrValue)
	{
		const CMyString str("");
		BOOST_CHECK_THROW(str[0], std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(AssignmentToIndex)
	{
		CMyString str("123");
		str[0] = '3';
		BOOST_CHECK(strcmp(str.GetStringData(), "323") == 0);
	}

	BOOST_AUTO_TEST_CASE(AssignToOutOfRangeIndex)
	{
		CMyString str("123");
		BOOST_CHECK_THROW(str[3] = '4', std::out_of_range);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(BoolOperatorsTests)

	BOOST_AUTO_TEST_CASE(FirstOperandSmallerThanSecond)
	{
		const CMyString str1("12345");
		const CMyString str2("2345");
		BOOST_CHECK(str1 != str2);
		BOOST_CHECK(str1 < str2);
		BOOST_CHECK(str1 <= str2);
		BOOST_CHECK(str2 > str1);
		BOOST_CHECK(str2 >= str1);
	}

	BOOST_AUTO_TEST_CASE(StringsAreEqual)
	{
		const CMyString str1("12345");
		const CMyString str2("12345");
		BOOST_CHECK(str1 < str2 == false);
		BOOST_CHECK(str1 <= str2);
		BOOST_CHECK(str2 > str1 == false);
		BOOST_CHECK(str2 >= str1);
		BOOST_CHECK(str1 == str2);
	}

	BOOST_AUTO_TEST_CASE(SecondOperandSmallerThanFirst)
	{
		const CMyString str1("2345");
		const CMyString str2("123");
		BOOST_CHECK(str1 > str2);
		BOOST_CHECK(str2 <= str1);
		BOOST_CHECK(str2 < str1);
		BOOST_CHECK(str1 >= str2);
	}

	BOOST_AUTO_TEST_CASE(StringAreEqualButOneOfThemIsLonger)
	{
		const CMyString str("12345");
		const CMyString str2("123");
		BOOST_CHECK(str > str2);
		BOOST_CHECK(str2 > str == false);
		BOOST_CHECK(str2 <= str);
		BOOST_CHECK(str2 < str);
		BOOST_CHECK(str < str2 == false);
		BOOST_CHECK(str >= str2);
		BOOST_CHECK(str != str2);
	}

	BOOST_AUTO_TEST_CASE(StringWithSameLenButWithDifferentContent)
	{
		const CMyString str("15523");
		const CMyString str2("15534");
		BOOST_CHECK(str != str2);
		BOOST_CHECK(str < str2);
		BOOST_CHECK(str <= str2);
		BOOST_CHECK(str2 > str);
		BOOST_CHECK(str2 >= str);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ClearMethodTests)

	BOOST_AUTO_TEST_CASE(ClearEmptyStr)
	{
		CMyString str;
		str.Clear();
		BOOST_CHECK(str.GetStringData() == "");
		BOOST_CHECK(str.GetLength() == 0);
	}

	BOOST_AUTO_TEST_CASE(ClearStr)
	{
		CMyString str("Hello");
		str.Clear();
		BOOST_CHECK(str.GetStringData() == "");
		BOOST_CHECK(str.GetLength() == 0);
	}

	BOOST_AUTO_TEST_CASE(ClearStrAndThenAssign)
	{
		CMyString str("Hello");
		str.Clear();
		str = "Hello, world!";
		BOOST_CHECK(strcmp(str.GetStringData(), "Hello, world!") == 0);
		BOOST_CHECK(str.GetLength() == 13);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AssignmentOperator)

	BOOST_AUTO_TEST_CASE(AssignOneStrToAnother)
	{
		CMyString str1 = "I love C++";
		CMyString str2 = "I don't love Java";
		BOOST_CHECK(strcmp(str1.GetStringData(), "I love C++") == 0);
		str1 = str2;
		BOOST_CHECK(strcmp(str1.GetStringData(), "I don't love Java") == 0);
		BOOST_CHECK(str1.GetLength() == 17);
		BOOST_CHECK(strcmp(str2.GetStringData(), "I don't love Java") == 0);
		BOOST_CHECK(str2.GetLength() == 17);
	}

	BOOST_AUTO_TEST_CASE(AssignNotEmptyStrToEmpty)
	{
		CMyString str1;
		CMyString str2 = "Moscow";
		BOOST_CHECK(strcmp(str1.GetStringData(), "") == 0);
		str1 = str2;
		BOOST_CHECK(strcmp(str1.GetStringData(), "Moscow") == 0);
		BOOST_CHECK(str1.GetLength() == 6);
		BOOST_CHECK(strcmp(str2.GetStringData(), "Moscow") == 0);
		BOOST_CHECK(str2.GetLength() == 6);
	}

	BOOST_AUTO_TEST_CASE(AssignEmptyStrToNotEmpty)
	{
		CMyString str1;
		CMyString str2 = "Saint Petersburg";
		BOOST_CHECK(strcmp(str1.GetStringData(), "") == 0);
		str2 = str1;
		BOOST_CHECK(strcmp(str1.GetStringData(), "") == 0);
		BOOST_CHECK(str1.GetLength() == 0);
		BOOST_CHECK(strcmp(str2.GetStringData(), "") == 0);
		BOOST_CHECK(str2.GetLength() == 0);
	}

	BOOST_AUTO_TEST_CASE(MoveAssignmentOperator)
	{
		CMyString str1 = "Saint Petersburg";
		CMyString str2 = "Moscow";
		str1 = std::move(str2);
		BOOST_CHECK(strcmp(str1.GetStringData(), "Moscow") == 0);
		BOOST_CHECK(str1.GetLength() == 6);
		BOOST_CHECK(strcmp(str2.GetStringData(), "") == 0);
		BOOST_CHECK(str2.GetLength() == 0);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SubstringMethodTests)

	BOOST_AUTO_TEST_CASE(SelectSubstringFromNotEmptyString)
	{
		CMyString str = "Hello, world!";
		auto result = str.SubString(7, 6);
		BOOST_CHECK(strcmp(result.GetStringData(), "world!") == 0);
	}

	BOOST_AUTO_TEST_CASE(SelectSubstringWithOverflowedSize)
	{
		CMyString str = "Hello, world!";
		auto result = str.SubString(7, 15);
		BOOST_CHECK(result == "world!");
	}

	BOOST_AUTO_TEST_CASE(SelectSubstringWithOutOfRangePosition)
	{
		CMyString str = "Hello, world!";
		BOOST_CHECK_THROW(auto result = str.SubString(str.GetLength(), 100), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(SelectFullSubstring)
	{
		CMyString str = "Hello, world!";
		auto result = str.SubString(0, str.GetLength());
		BOOST_CHECK(result == str);
	}

	BOOST_AUTO_TEST_CASE(SelectSubstringFromEmptyStr)
	{
		CMyString str = "";
		BOOST_CHECK(str.GetLength() == 0);
		auto result = str.SubString(0, 10);
		BOOST_CHECK(result == "");
	}

	BOOST_AUTO_TEST_CASE(SelectSubstringFromEndOfStr)
	{
		CMyString str = "12345";
		auto result = str.SubString(4, 10);
		BOOST_CHECK(result == "5");
	}

	BOOST_AUTO_TEST_CASE(SelectSubstringFromOutOfRangeEnd)
	{
		CMyString str = "12345";
		BOOST_CHECK_THROW(auto result = str.SubString(5, 1), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(SelectSubstringWithZeroLength)
	{
		CMyString str = "12345";
		auto result = str.SubString(4, 0);
		BOOST_CHECK(result == "");
	}

BOOST_AUTO_TEST_SUITE_END()
