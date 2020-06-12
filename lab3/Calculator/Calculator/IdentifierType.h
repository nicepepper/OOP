#pragma once

#include <array>

enum class IdentifierType
{
	NO_TYPE,
	FUNCTION,
	VARIABLE
};

constexpr std::array<IdentifierType, 3> IdentifierTypes = {
	IdentifierType::NO_TYPE,
	IdentifierType::FUNCTION,
	IdentifierType::VARIABLE
};
