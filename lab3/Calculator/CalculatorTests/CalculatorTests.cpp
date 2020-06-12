#include "../Calculator/Calculator.h"
#define BOOST_TEST_MODULE CalculatorTest
#include <boost\test\unit_test.hpp>

namespace tt = boost::test_tools;

Calculator CreateCalcWithFunctions()
{
	Calculator calc;

	BOOST_CHECK(calc.SaveVariable("x", 100));
	BOOST_CHECK(calc.SaveVariable("y", 100));
	BOOST_CHECK(calc.SaveFunction("xplusy", "x", "+", "y"));
	BOOST_CHECK(calc.SaveFunction("xminusy", "x", "-", "y"));
	BOOST_CHECK(calc.SaveFunction("xmulty", "x", "*", "y"));
	BOOST_CHECK(calc.SaveFunction("xdivy", "x", "/", "y"));
	return calc;
}

BOOST_AUTO_TEST_SUITE(CalculatorTest)

	BOOST_AUTO_TEST_CASE(CheckIfExistsIdentifier)
	{
		auto calc = CreateCalcWithFunctions();
		bool exists = calc.DoesIdentifierExists("x") && calc.DoesIdentifierExists("y") && calc.DoesIdentifierExists("xplusy");
		exists = exists && calc.DoesIdentifierExists("xminusy") && calc.DoesIdentifierExists("xmulty") && calc.DoesIdentifierExists("xdivy");
		BOOST_CHECK(exists);
		BOOST_CHECK(calc.DoesIdentifierExists("dontexists") == false);
	}

	BOOST_AUTO_TEST_CASE(SaveEmptyVariable)
	{
		Calculator calc;
		BOOST_CHECK(calc.SaveVariable("x"));
		float value;
		BOOST_CHECK(calc.GetIdentifierValue("x", value) == false);
	}

	BOOST_AUTO_TEST_CASE(CannotSaveSameVariableTwice)
	{
		Calculator calc;
		BOOST_CHECK(calc.SaveVariable("x"));
		BOOST_CHECK(calc.SaveVariable("x") == false);
	}

	BOOST_AUTO_TEST_CASE(CannotSaveEmptyString)
	{
		Calculator calc;

		BOOST_CHECK(calc.SaveVariable("") == false);
	}

	BOOST_AUTO_TEST_CASE(CannotAssignValueToFunction)
	{
		auto calc = CreateCalcWithFunctions();
		BOOST_CHECK(calc.SaveVariable("xdivy", 100) == false);
	}

	BOOST_AUTO_TEST_CASE(CannotSaveFuncWhichExists)
	{
		auto calc = CreateCalcWithFunctions();
		BOOST_CHECK(calc.SaveFunction("xdivy", "x", "/", "y") == false);
	}

	BOOST_AUTO_TEST_CASE(CannotAssignUndefinedVariable)
	{
		auto calc = CreateCalcWithFunctions();
		BOOST_CHECK(calc.AssignSecondVariableToFirst("x", "undfndvar") == false);
	}

	BOOST_AUTO_TEST_CASE(AssignTwoDefinedVariables)
	{
		auto calc = CreateCalcWithFunctions();
		BOOST_CHECK(calc.AssignSecondVariableToFirst("x", "y"));
	}

	BOOST_AUTO_TEST_CASE(CountFibonachiNumbers)
	{
		Calculator calc;

		BOOST_CHECK(calc.SaveVariable("v0", 0));
		BOOST_CHECK(calc.SaveVariable("v1", 1));
		BOOST_CHECK(calc.SaveFunction("fib0", "v0"));
		BOOST_CHECK(calc.SaveFunction("fib1", "v1"));
		BOOST_CHECK(calc.SaveFunction("fib2", "fib1", "+", "fib0"));
		BOOST_CHECK(calc.SaveFunction("fib3", "fib2", "+", "fib1"));
		BOOST_CHECK(calc.SaveFunction("fib4", "fib3", "+", "fib2"));
		BOOST_CHECK(calc.SaveFunction("fib5", "fib4", "+", "fib3"));
		BOOST_CHECK(calc.SaveFunction("fib6", "fib5", "+", "fib4"));
		BOOST_CHECK(calc.SaveFunction("fib7", "fib6", "+", "fib5"));
		BOOST_CHECK(calc.SaveFunction("fib8", "fib7", "+", "fib6"));
		BOOST_CHECK(calc.SaveFunction("fib9", "fib8", "+", "fib7"));
		BOOST_CHECK(calc.SaveFunction("fib10", "fib9", "+", "fib8"));

		float value;

		BOOST_CHECK(calc.GetIdentifierValue("fib10", value));
		BOOST_TEST(value == 55, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(CountFuncWithUninitializedVars)
	{
		Calculator calc;

		BOOST_CHECK(calc.SaveVariable("v0"));
		BOOST_CHECK(calc.SaveVariable("v1", 1));
		BOOST_CHECK(calc.SaveFunction("fib0", "v0"));
		BOOST_CHECK(calc.SaveFunction("fib1", "v1"));
		BOOST_CHECK(calc.SaveFunction("fib2", "fib1", "+", "fib0"));

		float value;

		BOOST_CHECK(calc.GetIdentifierValue("fib10", value) == false);
	}

	BOOST_AUTO_TEST_CASE(CalcFuncsResult)
	{
		auto calc = CreateCalcWithFunctions();

		float value;

		BOOST_CHECK(calc.GetIdentifierValue("xminusy", value));
		BOOST_TEST(value == 0, tt::tolerance(0.001));

		BOOST_CHECK(calc.GetIdentifierValue("xplusy", value));
		BOOST_TEST(value == 200, tt::tolerance(0.001));

		BOOST_CHECK(calc.GetIdentifierValue("xmulty", value));
		BOOST_TEST(value == 10000, tt::tolerance(0.001));

		BOOST_CHECK(calc.GetIdentifierValue("xdivy", value));
		BOOST_TEST(value == 1, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(CalcCanSaveOnlyFuncsWithOperationsAsThirdParam)
	{
		auto calc = CreateCalcWithFunctions();

		BOOST_CHECK(calc.SaveFunction("xy", "x", "p", "y") == false);
		BOOST_CHECK(calc.SaveFunction("xy", "x", "", "y") == false);
		BOOST_CHECK(calc.SaveFunction("xy", "x", "123", "y") == false);
	}

	BOOST_AUTO_TEST_CASE(AssignNullValue)
	{
		Calculator calc;
		calc.SaveVariable("x", 100);
		calc.SaveVariable("y");
		float value = 0;
		BOOST_CHECK(calc.AssignSecondVariableToFirst("x", "y"));
		BOOST_CHECK(calc.GetIdentifierValue("x", value) == false);
	}

	BOOST_AUTO_TEST_CASE(CountFuncWhichAreLinksToVars)
	{
		auto calc = CreateCalcWithFunctions();
		float xVal, yVal, xFuncVal, yFuncVal;
		BOOST_CHECK(calc.SaveFunction("xlink", "x"));
		BOOST_CHECK(calc.SaveFunction("ylink", "y"));

		BOOST_CHECK(calc.GetIdentifierValue("xlink", xFuncVal));
		BOOST_CHECK(calc.GetIdentifierValue("x", xVal));

		BOOST_CHECK(calc.GetIdentifierValue("ylink", yFuncVal));
		BOOST_CHECK(calc.GetIdentifierValue("y", yVal));

		BOOST_TEST(xVal == xFuncVal, tt::tolerance(0.001));
		BOOST_TEST(yVal == yFuncVal, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(GetNamesOfFuncsAndVars)
	{
		auto calc = CreateCalcWithFunctions();
		BOOST_CHECK(calc.SaveFunction("badfunc", "x", "", "y") == false);
		BOOST_CHECK(calc.AssignSecondVariableToFirst("badvar", "badvar2") == false);
		std::set<std::string> mustReturnVarsNames = { "x", "y" };
		BOOST_TEST(mustReturnVarsNames == calc.GetVariablesNames());
		std::set<std::string> mustReturnFnsNames = { "xplusy", "xminusy", "xmulty", "xdivy" };
		BOOST_TEST(mustReturnFnsNames == calc.GetFunctionsNames());
	}

BOOST_AUTO_TEST_SUITE_END()