#include "CalculatorFunc.h"

CalculatorFunc::CalculatorFunc(const std::string& firstOperator, Operation operation, const std::string& secondOperator)
	: CalcuatorIdentifier(IdentifierType::FUNCTION)
	, m_isLink(false)
	, m_firstOperator(firstOperator)
	, m_operation(operation)
	, m_secondOperator(secondOperator)
{
}

CalculatorFunc::CalculatorFunc(const std::string& linkName)
	: CalcuatorIdentifier(IdentifierType::FUNCTION)
	, m_isLink(true)
	, m_operation(Operation::NO_OPERATION)
	, m_linkName(linkName)
{
}

std::string CalculatorFunc::GetFirstOperator()
{
	return m_firstOperator;
}

std::string CalculatorFunc::GetSecondOperator()
{
	return m_secondOperator;
}

Operation CalculatorFunc::GetOperation()
{
	return m_operation;
}

bool CalculatorFunc::IsLink()
{
	return m_isLink;
}

std::string& CalculatorFunc::GetLinkName()
{
	return m_linkName;
}
