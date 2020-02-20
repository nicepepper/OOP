#pragma once
#include <string>
#include <optional>

struct AppParams
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<AppParams> ParseCommandLine(int size, char* arguments[]);