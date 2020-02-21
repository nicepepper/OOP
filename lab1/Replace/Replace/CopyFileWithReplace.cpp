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
