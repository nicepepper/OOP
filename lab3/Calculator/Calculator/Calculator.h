#pragma once
#include "Operation.h"
#include "IdentifiersStorage.h"
#include <set>
#include <string>

class Calculator
{
public:
	Calculator();
	std::set<std::string> GetVariablesNames() const;
	std::set<std::string> GetFunctionsNames() const;
	bool DoesIdentifierExists(const std::string& name) const;
	bool GetIdentifierValue(const std::string& name, float& value);
	bool AssignSecondVariableToFirst(const std::string& first, const std::string& second);
	bool SaveFunction(const std::string& name, const std::string& firstOperand, const std::string& operatio, const std::string& secondOperand);
	bool SaveFunction(const std::string& name, const std::string& linkName);
	bool SaveVariable(const std::string& name);
	bool SaveVariable(const std::string& name, float value);

private:
	float CalculateIdentifier(const std::string& name, bool& isTrue);
	float CalculateFunctionResult(CalculatorFunc& func, bool& isTrue);
	IdentifiersStorage m_storage;
};
