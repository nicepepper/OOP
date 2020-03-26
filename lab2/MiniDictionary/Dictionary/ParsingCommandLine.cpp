#include "ParsingCommandLine.h"
const int NUMBER_OF_PARAMETRS = 2;

std::optional<ProgramParametrs> ParseComandLine(int size, char* arguments[])
{
	if (size != NUMBER_OF_PARAMETRS)
	{
		return std::nullopt;
	}
	ProgramParametrs params;
	params.inputFileName = arguments[1];
	return params;
}
