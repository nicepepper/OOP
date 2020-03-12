#pragma once

#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

struct ProgramParametrs
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<ProgramParametrs> ParseComandLine(int size, char* arguments[]);
