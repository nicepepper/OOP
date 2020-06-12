#pragma once
#include "CalcuatorIdentifier.h"

class CalculatorVar : public CalcuatorIdentifier
{
public:
	CalculatorVar();
	CalculatorVar(float value);
	float GetValue();
	void SetValue(float value);
	bool HasValue();
	void MakeNullable();

private:
	bool m_isValueSet;
	float m_value;
};
