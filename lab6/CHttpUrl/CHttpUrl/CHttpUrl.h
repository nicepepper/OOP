#pragma once
#include "CUrlParsingError.h"
#include "Protocol.h"
#include <string>

class CHttpUrl
{
public:
	explicit CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& protocol, const std::string& domain, int port, const std::string& document);
	CHttpUrl(const std::string& protocol, const std::string& domain, const std::string& document);
	CHttpUrl(const std::string& protocol, const std::string& domain);
	CHttpUrl(const std::string& protocol, const std::string& domain, int port);
	~CHttpUrl() = default;

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;

	int GetPort() const;
	static bool IsProtocolValid(const std::string& protocol);
	static std::string UpdateDocumentWithBackslashIfNeeds(const std::string& document);

private:
	void BuildURLString();
	std::string m_url;
	Protocol m_protocol;
	std::string m_domain;
	int m_port;
	std::string m_document;
};
