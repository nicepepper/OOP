#include "CopyFileWithReplace.h"

std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{

	if (subject.empty() || searchString.empty())
	{
		return subject;
	}
	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

bool CopyWithReplace(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchString, const std::string& replaceString)
{
	std::ifstream input(inputFileName);
	std::ofstream output(outputFileName, std::ios::out | std::ios::trunc);

	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for writing\n";
		return false;
	}

	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	CopyFileWithReplace(input, output, searchString, replaceString);

	if (input.bad())
	{
		std::cout << "Faild to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file!" << std::endl;
		return false;
	}
	return true;
}
