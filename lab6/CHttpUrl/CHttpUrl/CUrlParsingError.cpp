#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const ErrorType error, const std::string& invalidPathOfUrl)
	: std::invalid_argument(CreateParsingErrorMessage(error, invalidPathOfUrl))
{
}

std::string CUrlParsingError::CreateParsingErrorMessage(const ErrorType error, const std::string& invalidPathOfUrl)
{
	std::string message;
	switch (error)
	{
	case INVALID_URL:
		message += "Filed to parse URL: \"";
		break;

	case INVALID_PROTOCOL:
		message += "The URL has invalid protocol: \"";
		break;

	case INVALID_DOMAIN:
		message += "The URL has invalid domain: \"";
		break;

	case INVALID_PORT:
		message += "The URL has invalid port: \"";
		break;

	case PORT_OUT_OF_RANGE:
		message += "The URL`s port is out of range: \"";
		break;
	}
	message += invalidPathOfUrl + "\"";
	return message;
}