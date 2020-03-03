#pragma once
#include <optional>
#include <string>

enum Mode
{
	pack,
	unpack
};

struct ProgramParameters
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<ProgramParameters> ParseComandLine(int size, char* arguments[]);
