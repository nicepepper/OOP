#include "IdentifiersStorage.h"

IdentifiersStorage::IdentifiersStorage()
{
	for (const auto id : IdentifierTypes)
	{
		m_namesOfIdentifiers.emplace(std::pair<IdentifierType, std::set<std::string>>(id, std::set<std::string>()));
	}
}

std::set<std::string> IdentifiersStorage::GetAllNamesOf(IdentifierType type) const
{
	return m_namesOfIdentifiers.find(type)->second;
}

bool IdentifiersStorage::DoesIdentifierExists(const std::string& name) const
{
	return (m_identifiers.find(name) != m_identifiers.end());
}

bool IdentifiersStorage::IsValidIdentifier(const std::string& name, IdentifierType type) const
{
	auto iter = m_identifiers.find(name);
	if (iter != m_identifiers.end())
	{
		return (*iter).second.type == type;
	}
	return false;
}

bool IdentifiersStorage::SaveIdentifier(const std::string& name, CalculatorVar& identifier)
{
	if (name.empty())
	{
		return false;
	}
	EraseIdentifier(name);
	Variant variant = identifier;
	IdentifiersStorage::Identifier id(variant, IdentifierType::VARIABLE);
	m_identifiers.emplace(std::pair<std::string, Identifier>(name, id));
	m_namesOfIdentifiers.find(IdentifierType::VARIABLE)->second.emplace(name);
	return true;
}

bool IdentifiersStorage::SaveIdentifier(const std::string& name, CalculatorFunc& identifier)
{
	if (name.empty())
	{
		return false;
	}
	EraseIdentifier(name);
	Variant variant = identifier;
	IdentifiersStorage::Identifier id(variant, IdentifierType::FUNCTION);
	m_identifiers.emplace(std::pair<std::string, Identifier>(name, id));
	m_namesOfIdentifiers.find(IdentifierType::FUNCTION)->second.emplace(name);
	return true;
}

IdentifiersStorage::Identifier* const IdentifiersStorage::GetIdentifier(const std::string& name)
{
	auto iter = m_identifiers.find(name);
	if (iter == m_identifiers.end())
	{
		return nullptr;
	}
	return &(*iter).second;
}

IdentifierType IdentifiersStorage::GetTypeOf(const std::string& name)
{
	auto ptr = GetIdentifier(name);
	if (ptr == nullptr)
	{
		return IdentifierType::NO_TYPE;
	}
	return ptr->type;
}

void IdentifiersStorage::EraseIdentifier(const std::string& name)
{
	if (DoesIdentifierExists(name))
	{
		auto iter = m_identifiers.find(name);
		IdentifierType type = iter->second.type;
		m_namesOfIdentifiers.find(type)->second.erase(name);
		m_identifiers.erase(iter);
	}
}
