#pragma once
#include "CalcuatorIdentifier.h"
#include "Operation.h"
#include <string>

class CalculatorFunc : public CalcuatorIdentifier
{
public:
	CalculatorFunc(const std::string& firstOperator, Operation operation, const std::string& secondOperator);
	CalculatorFunc(const std::string& linkName);
	std::string GetFirstOperator();
	std::string GetSecondOperator();
	Operation GetOperation();
	bool IsLink();
	std::string& GetLinkName();

private:
	bool m_isLink;
	std::string m_linkName;
	std::string m_firstOperator;
	std::string m_secondOperator;
	Operation m_operation;
};
