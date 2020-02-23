#pragma once
#include <optional>
#include <string>

struct Args
{
	std::string source;
	std::string destination;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
