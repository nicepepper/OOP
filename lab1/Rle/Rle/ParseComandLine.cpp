#include "ParseComandLine.h"
const int NUMBER_OF_PARAMETRS = 4;
const std::string PACK_MODE = "pack";
const std::string UNPACK_MODE = "unpack";

std::optional<Mode> GetMode(const std::string& modeString)
{
	if (modeString == PACK_MODE)
	{
		return pack;
	}

	if (modeString == UNPACK_MODE)
	{
		return unpack;
	}

	return std::nullopt;
}

std::optional<ProgramParameters> ParseComandLine(int size, char* arguments[])
{
	if (size != NUMBER_OF_PARAMETRS)
	{
		return std::nullopt;
	}
	ProgramParameters params;

	auto mode = GetMode(arguments[1]);

	return std::optional<ProgramParameters>();
}
