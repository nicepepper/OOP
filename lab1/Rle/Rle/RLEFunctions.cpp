#include "RLEFunctions.h"

struct RLEChunk
{
	char currentValue = 0;
	unsigned char counter = 0;
};

bool SaveChunk(std::ostream& output, RLEChunk& chunk)
{
	if (!output.write(reinterpret_cast<char*>(&chunk.counter), sizeof chunk.counter))
	{
		return false;
	}
	if (!output.write(&chunk.currentValue, sizeof chunk.currentValue))
	{
		return false;
	}
	return true;
}

bool UpdateChunk(RLEChunk& chunk, char ch, bool eof, std::ostream& output)
{
	if (chunk.counter == 0)
	{
		chunk.currentValue = ch;
	}
	if ((chunk.currentValue == ch) && (chunk.counter < UCHAR_MAX))
	{
		chunk.counter++;
	}
	else
	{
		if (!SaveChunk(output, chunk))
		{
			std::cout << "Chunk conservation problem\n";
			return false;
		}
		chunk.counter = 0;
		if (!UpdateChunk(chunk, ch, eof, output))
		{
			return false;
		}
	}
	if ((eof) && (chunk.counter > 0))
	{
		if (!SaveChunk(output, chunk))
		{
			std::cout << "Chunk conservation problem\n";
			return false;
		}
	}
}

bool RLEEncoding(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream input(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream output(outputFileName, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	bool eof = false;
	char ch;
	RLEChunk chunk;

	auto fileSize = GetFileSize(inputFileName);
	for (std::uintmax_t i = 0; i < fileSize; i++)
	{
		eof = (i == fileSize - 1) ? true : false;
		if (input.get(ch))
		{
			if (!UpdateChunk(chunk, ch, eof, output))
			{
				break;
			}
		}
	}

	if (input.bad())
	{
		std::cout << "Faild to read data from input file\n";
		return false;
	}
	if (!output.flush())
	{
		std::cout << "Filed to write data to output file\n";
		return false;
	}
	return true;
}

bool ReadChunk(RLEChunk& chunk, std::istream& input)
{
	char ch;
	if (!input.get(ch))
	{
		return false;
	}
	chunk.counter = static_cast<unsigned char>(ch);
	if (chunk.counter == 0)
	{
		std::cout << "Zero character repetition" << std::endl;
		return false;
	}
	if (!input.get(chunk.currentValue))
	{
		return false;
	}
	return true;
}

bool WriteChunk(RLEChunk& chunk, std::ostream& output)
{
	for (std::uint8_t i = 0; i < static_cast<uint8_t>(chunk.counter); i++)
	{
		if (!output.write(&chunk.currentValue, sizeof chunk.currentValue))
		{
			return false;
		}
	}
	return true;
}

bool RLEDecoding(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream input(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream output(outputFileName, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	auto fileSize = GetFileSize(inputFileName);
	if (!IsFileSizeEven(fileSize))
	{
		std::cout << "Odd packed file length" << std::endl;
		return false;
	}

	RLEChunk chunk;
	for (std::uintmax_t i = 0; i < fileSize / 2; i++)
	{
		if (!ReadChunk(chunk, input))
		{
			std::cout << "Reading error\n";
			return false;
		}
		if (!WriteChunk(chunk, output))
		{
			std::cout << "Writing error\n";
			return false;
		}
	}

	if (input.bad())
	{
		std::cout << "Faild to read data from input file\n";
		return false;
	}
	if (!output.flush())
	{
		std::cout << "Filed to write data to output file\n";
		return false;
	}
	return true;
}
