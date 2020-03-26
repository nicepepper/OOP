#pragma once

#include <optional>
#include <string>

struct ProgramParametrs
{
	std::string inputFileName;
};

std::optional<ProgramParametrs> ParseComandLine(int size, char* arguments[]);
