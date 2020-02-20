#include "ReplaceSubstringsInTextFile.h"

std::string ReplaceSubstrings(const std::string& subject, const std::string& searchString, const std::string& replaceString)
{
	if (replaceString.length() == 0)
	{
		return subject;
	}

	std::string output;

	size_t currPosition = 0;

	size_t searchPosition = 0;

	while (searchPosition != std::string::npos)
	{
		searchPosition = subject.find(searchString, currPosition);

		if (searchPosition != std::string::npos)
		{
			output += subject.substr(currPosition, searchPosition - currPosition) + replaceString;
			currPosition = searchPosition + searchString.length();
		}
		else
		{
			output += subject.substr(currPosition);
		}

	}

	return output;
}

void ReplaceSubstringsInTextFile(std::istream& input, std::ofstream& output, const std::string& searchString, const std::string& replaceString)
{
	std::string str;

	while (std::getline(input, str))
	{
		output << ReplaceSubstrings(str, searchString, replaceString) << std::endl;
	}
}
