#include "InputParams.h"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5 || argv[1] == "" || argv[2] == "")
	{
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}
