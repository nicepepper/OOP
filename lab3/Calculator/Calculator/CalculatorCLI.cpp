#include "CalculatorCLI.h"
#include "Calculator.h"
#include "StringToFloat.h"
#include <regex>
#include <sstream>
#include <string>

bool RegexSearch(const std::string& searchString, const std::string&& pattern, std::smatch& match)
{
	std::regex regexp(pattern, std::regex_constants::icase);

	if (std::regex_search(searchString, match, regexp))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InitializeEmptyVariable(Calculator& calc, const std::string inStr)
{
	std::smatch match;

	if (RegexSearch(inStr, R"(^\s*var\s+([a-zA-Z]+\w*)\s*$)", match))
	{
		return calc.SaveVariable(match.str(1));
	}

	return false;
}

bool InitializeLetVariable(Calculator& calc, const std::string inStr)
{
	std::smatch match;

	if (!RegexSearch(inStr, R"(^\s*let\s+([a-zA-Z]+\w*)\s*=\s*(([a-zA-Z]+\w*)|(-?\d+\.?\d*))\s*$)", match))
	{
		return false;
	}

	if (match.str(3).size())
	{
		return calc.AssignSecondVariableToFirst(match.str(1), match.str(3));
	}

	if (match.str(4).size())
	{
		float numberVar = 0;

		if (StrToFloat(numberVar, match.str(4)))
		{
			return calc.SaveVariable(match.str(1), numberVar);
		}
	}

	return false;
}

bool InitFunction(Calculator& calc, const std::string inStr)
{
	std::smatch match;

	if (RegexSearch(inStr, R"(^\s*fn\s+([a-zA-Z]+\w*)\s*=\s*([a-zA-Z]+\w*)\s*(\+|\/|\*|-)\s*([a-zA-Z]+\w*)\s*$)", match))
	{
		return calc.SaveFunction(match.str(1), match.str(2), match.str(3), match.str(4));
	}
	else if (RegexSearch(inStr, R"(^\s*fn\s+([a-zA-Z]+\w*)\s*=\s*([a-zA-Z]+\w*)\s*$)", match))
	{
		return calc.SaveFunction(match.str(1), match.str(2));
	}
	return false;
}

std::string GetPrintedVariableName(const std::string& inStr)
{
	std::smatch match;

	if (RegexSearch(inStr, R"(^\s*print\s+([a-zA-Z]+\w*)\s*$)", match))
	{
		return match.str(1);
	}

	return std::string();
}

std::string GetAction(const std::string& inStr)
{
	std::string actStr;
	std::istringstream sstream(inStr);
	if (sstream >> actStr)
	{
		return actStr;
	}
	else
	{
		return std::string();
	}
}

void CalculatorCLI::HandlePrintingFunctionsValues()
{
	auto namesOfFuncs = calc.GetFunctionsNames();
	for (const std::string& name : namesOfFuncs)
	{
		HandlePrintingSingleVar(name);
	}
}

void CalculatorCLI::HandlePrintingSingleVar(const std::string& name)
{
	float result = 0;
	if (!calc.DoesIdentifierExists(name))
	{
		m_output << "An attempt to print the nonexistent identifier was caught" << std::endl;
		return;
	}
	if (calc.GetIdentifierValue(name, result))
	{
		m_output << name << ":" << result << std::endl;
	}
	else
	{
		m_output << name << ":NaN" << std::endl;
	}
}

void CalculatorCLI::HandlePrintingVarsValues()
{
	auto namesOfVars = calc.GetVariablesNames();
	for (const std::string& name : namesOfVars)
	{
		HandlePrintingSingleVar(name);
	}
}

void CalculatorCLI::ParseLineAndDoTheAction(const std::string& inStr)
{
	std::string act = GetAction(inStr);
	if (act == "var")
	{
		if (!InitializeEmptyVariable(calc, inStr))
		{
			m_output << "Failed to save that variable, probably this one already exists" << std::endl;
		}
		return;
	}

	if (act == "let")
	{
		if (!InitializeLetVariable(calc, inStr))
		{
			m_output << "Failed to save let variable. Identifier can not start with digit. Variable can not reference to another nonexistent variable" << std::endl;
		}
		return;
	}

	if (act == "fn")
	{
		if (!InitFunction(calc, inStr))
		{
			m_output << "Failed to save the function" << std::endl;
		}
		return;
	}

	if (act == "printfns")
	{
		HandlePrintingFunctionsValues();
		return;
	}

	if (act == "printvars")
	{
		HandlePrintingVarsValues();
		return;
	}

	if (act == "print")
	{
		HandlePrintingSingleVar(GetPrintedVariableName(inStr));
		return;
	}

	if (inStr.size() != 0)
	{
		m_output << "Unknown command, please check it and try again" << std::endl;
	}
}

CalculatorCLI::CalculatorCLI(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	std::string inStr;

	while (std::getline(m_input, inStr))
	{
		ParseLineAndDoTheAction(inStr);
	}
}