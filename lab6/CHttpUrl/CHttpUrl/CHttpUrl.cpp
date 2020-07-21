#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "URLUntils.h"
#include <regex>

CHttpUrl::CHttpUrl(const std::string& url)
{
	if (!ParseURL(url, m_protocol, m_port, m_domain, m_document))
	{
		throw CUrlParsingError(CUrlParsingError::INVALID_URL, url);
	}
	m_url = url;
	m_document = UpdateDocumentWithBackslashIfNeeds(m_document);
	BuildURLString();
}

CHttpUrl::CHttpUrl(const std::string& protocol, const std::string& domain, int port, const std::string& document)
{
	if (!IsProtocolValid(protocol))
	{
		throw CUrlParsingError(CUrlParsingError::INVALID_PROTOCOL, protocol);
	}
	if (!IsDomainValid(domain))
	{
		throw CUrlParsingError(CUrlParsingError::INVALID_DOMAIN, domain);
	}
	if (!IsPortInRange(port))
	{
		throw CUrlParsingError(CUrlParsingError::PORT_OUT_OF_RANGE, std::to_string(port));
	}
	m_protocol = StringProtocolToEnum(protocol);
	m_domain = domain;
	m_port = port;
	m_document = UpdateDocumentWithBackslashIfNeeds(document);
	BuildURLString();
}

CHttpUrl::CHttpUrl(const std::string& protocol, const std::string& domain, const std::string& document)
	: CHttpUrl(protocol, domain, 1, document)
{
	m_port = GetDefaultPort(m_protocol);
	BuildURLString();
}

CHttpUrl::CHttpUrl(const std::string& protocol, const std::string& domain)
	: CHttpUrl(protocol, domain, std::string())
{
}

CHttpUrl::CHttpUrl(const std::string& protocol, const std::string& domain, const int port)
	: CHttpUrl(protocol, domain, port, std::string())
{
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

int CHttpUrl::GetPort() const
{
	return m_port;
}

bool CHttpUrl::IsProtocolValid(const std::string& protocol)
{
	try
	{
		StringProtocolToEnum(protocol);
		return true;
	}
	catch (std::exception&)
	{
		return false;
	}
}

std::string CHttpUrl::UpdateDocumentWithBackslashIfNeeds(const std::string& document)
{
	if (document.empty())
	{
		return "/";
	}
	if (document[0] == '/')
	{
		return document;
	}
	return "/" + document;
}

void CHttpUrl::BuildURLString()
{
	m_url = EnumProtocolToString(m_protocol) + "://" + m_domain;
	if (GetDefaultPort(m_protocol) != m_port)
	{
		m_url += ':' + std::to_string(m_port);
	}
	m_url += m_document;
}
