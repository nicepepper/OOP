#pragma once
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

enum class Mode 
{
	PACK,
	UNPACK
};

uintmax_t GetFileSize(const std::string& fileName);
bool IsFileSizeEven(const uintmax_t& number);

struct ProgramParameters
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<ProgramParameters> ParseComandLine(int size, char* arguments[]);
