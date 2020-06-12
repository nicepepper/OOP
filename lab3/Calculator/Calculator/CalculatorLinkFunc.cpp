#include "CalculatorLinkFunc.h"

CalculatorLinkFunc::CalculatorLinkFunc(const std::string& linkName)
	: m_linkName(linkName)
{

}

std::string& CalculatorLinkFunc::GetLinkName()
{
	return m_linkName;
}
