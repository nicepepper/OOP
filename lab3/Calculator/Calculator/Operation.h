#pragma once
#include <string>

enum class Operation
{
	NO_OPERATION,
	ADDITION,
	SUBTRACTION,
	DIVISION,
	MULTIPLE
};

Operation StringToOperation(const std::string& str);

float CountResult(float firstOperand, Operation operation, float secondOperand, bool& isTrue); //GetCalculationResult
