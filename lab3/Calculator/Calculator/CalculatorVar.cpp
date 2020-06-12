#include "CalculatorVar.h"

CalculatorVar::CalculatorVar()
	: CalcuatorIdentifier(IdentifierType::VARIABLE)
	, m_value(0)
	, m_isValueSet(false)
{
}

CalculatorVar::CalculatorVar(float value)
	: CalcuatorIdentifier(IdentifierType::VARIABLE)
	, m_value(value)
	, m_isValueSet(true)
{
}

float CalculatorVar::GetValue()
{
	return m_value;
}

void CalculatorVar::SetValue(float value)
{
	m_isValueSet = true;
	m_value = value;
}

bool CalculatorVar::HasValue()
{
	return m_isValueSet;
}

void CalculatorVar::MakeNullable()
{
	m_isValueSet = false;
	m_value = 0;
}
