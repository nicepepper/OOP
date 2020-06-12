#pragma once
#include <string>

class CalculatorLinkFunc
{
public:
	CalculatorLinkFunc(const std::string& linkName);
	std::string& GetLinkName();

private:
	std::string m_linkName;
};
