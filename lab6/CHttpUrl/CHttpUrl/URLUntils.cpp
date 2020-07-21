#include "URLUntils.h"
#include <regex>

const std::regex VALIDATE_DOMAIN_REGEX(R"(^(?:w{3}\.)?[A-Za-z0-9-_]+\.[A-Za-z0-9]+$)");
const std::regex PARSE_URL_REGEX(R"(^(http|https):\/\/((?:www\.)?[a-zA-Z0-9_-]+\.[A-Za-z0-9]+)(?:\:(\d+))?(?:\/(\S*))?$)", std::regex_constants::icase);

std::string WordToLowerCase(const std::string& word)
{
	std::string lowerCaseWord = word;
	std::transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), ::tolower);
	return lowerCaseWord;
}

Protocol StringProtocolToEnum(std::string protocol)
{
	protocol = WordToLowerCase(protocol);
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw std::exception("Unknown protocol type");
}

std::string EnumProtocolToString(const Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";

	case Protocol::HTTPS:
		return "https";

	default:
		throw std::exception("Unknown protocol type");
	}
}

bool StrToInt(const std::string& number, int& value)
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
	case Protocol::HTTPS:
		return 443;
	default:
		throw std::exception("Unknown protocol type");
	}
}

bool HandleMatchedValues(const std::smatch& match, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	const Protocol proto = StringProtocolToEnum(match.str(1));
	if (!match.str(3).empty())
	{
		int value = 0;

		if (StrToInt(match.str(3), value) && IsPortInRange(value))
		{
			port = value;
		}
		else
		{
			return false;
		}
	}
	else
	{
		port = GetDefaultPort(proto);
	}
	protocol = proto;
	host = match.str(2);
	document = match.str(4);
	return true;
}

bool IsPortInRange(int port)
{
	return (port >= 0) && (port <= USHRT_MAX);
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::smatch match;
	return std::regex_search(url, match, PARSE_URL_REGEX) && HandleMatchedValues(match, protocol, port, host, document);
}

bool IsDomainValid(const std::string& str)
{
	return std::regex_match(str, VALIDATE_DOMAIN_REGEX);
}
