#include "Operation.h"

Operation StringToOperation(const std::string& str)
{
	return (str == "+") ? Operation::ADDITION : (str == "-") ? Operation::SUBTRACTION : (str == "/") ? Operation::DIVISION : (str == "*") ? Operation::MULTIPLE : Operation::NO_OPERATION;
}

float CountResult(float firstOperand, Operation operation, float secondOperand, bool& isTrue)
{
	switch (operation)
	{
	case Operation::ADDITION:
		return firstOperand + secondOperand;
	case Operation::SUBTRACTION:
		return firstOperand - secondOperand;
	case Operation::DIVISION:
		if (secondOperand != 0)
		{
			return firstOperand / secondOperand;
		}
	case Operation::MULTIPLE:
		return firstOperand * secondOperand;
	};

	isTrue = false;
	return 0;
}
