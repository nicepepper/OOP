#pragma once
#include <stdexcept>

class CUrlParsingError final : public std::invalid_argument
{
public:
	enum ErrorType
	{
		INVALID_URL,
		INVALID_PROTOCOL,
		INVALID_DOMAIN,
		INVALID_PORT,
		PORT_OUT_OF_RANGE
	};

	explicit CUrlParsingError(ErrorType error, const std::string& invalidPathOfUrl);
	CUrlParsingError(CUrlParsingError&&) = default;
	CUrlParsingError(CUrlParsingError&) = default;
	CUrlParsingError& operator=(CUrlParsingError&&) = default;
	~CUrlParsingError() = default;
	static std::string CreateParsingErrorMessage(ErrorType error, const std::string& invalidPathOfUrl);
};