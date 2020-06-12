#pragma once
#include "CalcuatorIdentifier.h"
#include "CalculatorFunc.h"
#include "CalculatorLinkFunc.h"
#include "CalculatorVar.h"
#include <map>
#include <set>
#include <string>
#include <variant>

class IdentifiersStorage
{
public:
	IdentifiersStorage();

	using Variant = std::variant<CalculatorVar, CalculatorFunc, CalculatorLinkFunc>;
	struct Identifier
	{
		Identifier(Variant& variant, IdentifierType type)
			: identifier(variant)
			, type(type)
		{
		}
		Variant identifier;
		IdentifierType type;
	};

	std::set<std::string> GetAllNamesOf(IdentifierType type) const;
	bool DoesIdentifierExists(const std::string& name) const;
	bool IsValidIdentifier(const std::string& name, IdentifierType type) const;
	bool SaveIdentifier(const std::string& name, CalculatorVar& identifier);
	bool SaveIdentifier(const std::string& name, CalculatorFunc& identifier);
	
	IdentifiersStorage::Identifier* const GetIdentifier(const std::string& name);
	IdentifierType GetTypeOf(const std::string& name);

private:
	void EraseIdentifier(const std::string& name);
	std::map<IdentifierType, std::set<std::string>> m_namesOfIdentifiers;
	std::set<std::string> m_varsNames;
	std::set<std::string> m_functionsName;
	std::map<std::string, Identifier> m_identifiers;
};
