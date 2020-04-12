#include "ParseURL.h"

const std::string PATTERN = R"(^(http|https|ftp):\/\/(www\..*?\.\w+)(?:\:(\d+))?(?:\/(\S*))?$)";

std::string WordToLowerCase(const std::string& word)
{
	std::string lowerCaseWord = word;
	std::transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), tolower);
	return lowerCaseWord;
}

Protocol GetEnumProtocolFromString(std::string protocol)
{
	protocol = WordToLowerCase(protocol);
	return 
		(protocol == "http") ? Protocol::HTTP :
		(protocol == "https") ? Protocol::HTTPS : 
		(protocol == "ftp") ? Protocol::FTP : Protocol::UNKNOWN;
}

bool StringToInt(const std::string& number, int& value)
{
	try
	{
		value = std::stoi(number);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
		break;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	default:
		return 0;
	}
}

void HandleMatchedValues(const std::smatch& match, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	protocol = GetEnumProtocolFromString(match.str(1));
	host = match.str(2);
	document = match.str(4);

	if (match.str(3).size())
	{
		int value = 0;

		if (StringToInt(match.str(3), value))
		{
			port = value;
			return;
		}
	}
	port = GetDefaultPort(protocol);
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::smatch match;
	std::regex regexPattern(PATTERN, std::regex_constants::icase);
	if (std::regex_search(url, match, regexPattern))
	{
		HandleMatchedValues(match, protocol, port, host, document);
	}
	else
	{
		return false;
	}
	return true;
}
