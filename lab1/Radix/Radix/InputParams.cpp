#include "InputParams.h"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4 || argv[1] == "" || argv[2] == "" || argv[3] == "")
	{
		return std::nullopt;
	}
	Args args;
	args.source = argv[1];
	args.destination = argv[2];
	args.value = argv[3];
	return args;
}
