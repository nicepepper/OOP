#include "RLEFunctions.h"

struct RLEItemStatuses
{
	bool eof = false;
	char ch = 0;
	char currentValue = 0;
	unsigned char counter = 0;
};

void PrintEncoded(std::ostream& output, RLEItemStatuses& itemStatuses)
{
	output.write(reinterpret_cast<char*>(&itemStatuses.counter), sizeof itemStatuses.counter);
	output.write(&itemStatuses.currentValue, sizeof itemStatuses.currentValue);
}

void DescriptorEncodingOperation(RLEItemStatuses& itemStatuses, std::ostream& output)
{
	if (itemStatuses.counter == 0)
	{
		itemStatuses.currentValue = itemStatuses.ch;
	}

	if ((itemStatuses.currentValue == itemStatuses.ch) && (itemStatuses.ch < UCHAR_MAX))
	{
		itemStatuses.counter++;
	}
	else
	{
		if (itemStatuses.counter > 0 || itemStatuses.counter == UCHAR_MAX)
		{
			PrintEncoded(output, itemStatuses);
			itemStatuses.counter = 0;
			DescriptorEncodingOperation(itemStatuses, output);
			return;
		}
	}

	if (itemStatuses.eof && itemStatuses.counter > 0)
	{
		PrintEncoded(output, itemStatuses);
	}
}

bool IsSuccessfulEcoding(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream input(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream output(outputFileName, std::ios::binary);

	if (!input.is_open())
	{
		return false;
	}

	RLEItemStatuses itemStatuses;

	auto fileSize = GetFileSize(inputFileName);
	for (std::uintmax_t i = 0; i < fileSize; i++)
	{
		itemStatuses.eof = (i == fileSize - 1) ? true : false;
		if (input.good())
		{
			input.get(itemStatuses.ch);
			DescriptorEncodingOperation(itemStatuses, output);
		}
	}

	output.flush();
	return true;
}

bool IsSuccessfulDecoding(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream input(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream output(outputFileName, std::ios::binary | std::ios::out | std::ios::trunc);

	auto fileSize = GetFileSize(inputFileName);

	if (!IsFileSizeEven(fileSize))
	{
		return false;
	}

	char counter;
	char ch;

	for (std::uintmax_t i = 0; i < fileSize / 2; i++)
	{
		input.get(counter);
		input.get(ch);

		for (std::uint8_t i = 0; i < static_cast<uint8_t>(counter); i++)
		{
			output.write(&ch, sizeof ch);
		}
	}

	output.flush();
	return true;
}
