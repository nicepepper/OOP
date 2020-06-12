#include "StringToFloat.h"

bool StrToFloat(float& number, const std::string& str)
{
	try
	{
		number = std::stof(str);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}
