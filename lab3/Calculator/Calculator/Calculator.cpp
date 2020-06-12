#include "Calculator.h"

Calculator::Calculator()
{
}

bool Calculator::DoesIdentifierExists(const std::string& name) const
{
	return m_storage.DoesIdentifierExists(name);
}

std::set<std::string> Calculator::GetFunctionsNames() const
{
	return m_storage.GetAllNamesOf(IdentifierType::FUNCTION);
}

std::set<std::string> Calculator::GetVariablesNames() const
{
	return m_storage.GetAllNamesOf(IdentifierType::VARIABLE);
}

bool Calculator::GetIdentifierValue(const std::string& name, float& value)
{
	IdentifiersStorage::Identifier* ptrToId = m_storage.GetIdentifier(name);

	if (ptrToId == nullptr)
	{
		return false;
	}

	bool isOK = true;
	float val = CalculateIdentifier(name, isOK);

	if (isOK)
	{
		value = val;
	}
	return isOK;
}

bool Calculator::SaveFunction(const std::string& name, const std::string& firstOperand, const std::string& operation, const std::string& secondOperand)
{
	Operation funcOperation = StringToOperation(operation);
	bool areParamsValid = (funcOperation != Operation::NO_OPERATION) && m_storage.DoesIdentifierExists(firstOperand) && m_storage.DoesIdentifierExists(secondOperand) && !m_storage.DoesIdentifierExists(name);

	if (!areParamsValid)
	{
		return false;
	}

	CalculatorFunc fn(firstOperand, funcOperation, secondOperand);
	return m_storage.SaveIdentifier(name, fn);
}

bool Calculator::SaveFunction(const std::string& name, const std::string& linkName)
{
	if (m_storage.DoesIdentifierExists(name))
	{
		return false;
	}
	CalculatorFunc fn(linkName);
	return m_storage.SaveIdentifier(name, fn);
}

bool Calculator::SaveVariable(const std::string& name)
{
	if (m_storage.DoesIdentifierExists(name))
	{
		return false;
	}
	CalculatorVar var;
	return m_storage.SaveIdentifier(name, var);
}

bool Calculator::SaveVariable(const std::string& name, float value)
{
	if (m_storage.DoesIdentifierExists(name) && (m_storage.GetTypeOf(name) != IdentifierType::VARIABLE))
	{
		return false;
	}
	CalculatorVar var(value);
	return m_storage.SaveIdentifier(name, var);
}

bool Calculator::AssignSecondVariableToFirst(const std::string& first, const std::string& second)
{
	if (!DoesIdentifierExists(second))
	{
		return false;
	}

	if (!DoesIdentifierExists(first))
	{
		CalculatorVar var;

		m_storage.SaveIdentifier(first, var);
	}

	if ((m_storage.GetTypeOf(first) != IdentifierType::VARIABLE) || (m_storage.GetTypeOf(second) != IdentifierType::VARIABLE))
	{
		return false;
	}

	IdentifiersStorage::Identifier* ptrTofirst = m_storage.GetIdentifier(first);
	IdentifiersStorage::Identifier* ptrToSecond = m_storage.GetIdentifier(second);

	CalculatorVar& var1 = std::get<CalculatorVar>(ptrTofirst->identifier);
	CalculatorVar& var2 = std::get<CalculatorVar>(ptrToSecond->identifier);

	if (var2.HasValue())
	{
		var1.SetValue(var2.GetValue());
	}
	else
	{
		var1.MakeNullable();
	}

	return true;
}

float Calculator::CalculateIdentifier(const std::string& name, bool& isOK)
{
	auto ptr = m_storage.GetIdentifier(name);
	auto type = m_storage.GetTypeOf(name);

	if (type == IdentifierType::FUNCTION)
	{
		CalculatorFunc& fn = std::get<CalculatorFunc>(ptr->identifier);

		return CalculateFunctionResult(fn, isOK);
	}
	else if (type == IdentifierType::VARIABLE)
	{
		CalculatorVar& var = std::get<CalculatorVar>(ptr->identifier);

		if (!var.HasValue())
		{
			isOK = false;
			return 0;
		}

		return var.GetValue();
	}
	else
	{
		isOK = false;

		return 0;
	}
}

float Calculator::CalculateFunctionResult(CalculatorFunc& func, bool& isOK)
{
	if (func.IsLink())
	{
		return CalculateIdentifier(func.GetLinkName(), isOK);
	}
	else
	{
		float value1 = CalculateIdentifier(func.GetFirstOperator(), isOK);

		float value2 = CalculateIdentifier(func.GetSecondOperator(), isOK);

		return CountResult(value1, func.GetOperation(), value2, isOK);
	}
}
