#include "ParseComandLine.h"
const int NUMBER_OF_PARAMETRS = 4;
const std::string PACK_MODE = "pack";
const std::string UNPACK_MODE = "unpack";

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

bool IsFileSizeEven(const uintmax_t& number)
{
	return (number % 2 == 0);
}

std::optional<Mode> GetMode(const std::string& modeString)
{
	if (modeString == PACK_MODE)
	{
		return Mode::PACK;
	}

	if (modeString == UNPACK_MODE)
	{
		return Mode::UNPACK;
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

	if (mode && DoesFileExists(arguments[2]) && std::strlen(arguments[3]))
	{
		params.mode = *mode;
		params.inputFileName = arguments[2];
		params.outputFileName = arguments[3];

		return params;
	}
	else
	{
		return std::nullopt;
	}
}
