#pragma once

#include "Calculator.h"
#include <fstream>
#include <string>

class CalculatorCLI
{
public:
	CalculatorCLI(std::istream& input, std::ostream& output);

private:
	void HandlePrintingFunctionsValues();
	void HandlePrintingVarsValues();
	void HandlePrintingSingleVar(const std::string& name);
	void ParseLineAndDoTheAction(const std::string& inStr);

	std::istream& m_input;
	std::ostream& m_output;
	Calculator calc;
};
