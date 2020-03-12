#include "ParseCommandLine.h"
const int NUMBER_OF_PARAMETRS = 3;

namespace fs = std::filesystem;

bool DoesFileExists(const std::string& fileName)
{
	return fs::exists(fileName);
}

uintmax_t GetFileSize(const std::string& fileName)
{
	try
	{
		return fs::file_size(fileName);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		return 0;
	}
}

std::optional<ProgramParametrs> ParseComandLine(int size, char* arguments[])
{
	if (size == NUMBER_OF_PARAMETRS)
	{
		return std::nullopt;
	}
	ProgramParametrs params;
	if (DoesFileExists(arguments[1]) && std::strlen(arguments[2]))
	{
		params.inputFileName = arguments[1];
		params.outputFileName = arguments[2];
		return params;
	}
	else
	{
		return std::nullopt;
	}
}
