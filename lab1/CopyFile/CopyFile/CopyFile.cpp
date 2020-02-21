// CopyFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Invalid arguments cout \n";
		std::cout << "Usage CopiFile.exe <input file name> <output file name>\n";
		return 1;
	}

	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}

	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}

	if (input.bad())
	{
		std::cout << "Faild to read data from input file\n";
		return 1;
	}

	if (!output.flush())
	{
		std::cout << "Filed to write data to output file\n";
		return 1;
	}
	return 0;
}
