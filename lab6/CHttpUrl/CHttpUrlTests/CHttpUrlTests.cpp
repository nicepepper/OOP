#define BOOST_TEST_MODULE CHttpUrlTests
#include "../CHttpUrl/CHttpUrl.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ConstructorsTestsWithParsingUrl)

	BOOST_AUTO_TEST_CASE(InitFromUrlStringWithDocument)
	{
		const CHttpUrl url("https://www.youtube.com/watch?v=xB_SADktrus");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://www.youtube.com/watch?v=xB_SADktrus");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/watch?v=xB_SADktrus");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitFromUrlStringWithoutDocument)
	{
		const CHttpUrl url("https://www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://www.youtube.com/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitFromUrlStringWithHttpsProtocol)
	{
		const CHttpUrl url("https://www.youtube.com/watch?v=as1QfC2L0Og&list=PLyve-uz8m19DHjztFJlYPd61fq9qggRTD/");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://www.youtube.com/watch?v=as1QfC2L0Og&list=PLyve-uz8m19DHjztFJlYPd61fq9qggRTD/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/watch?v=as1QfC2L0Og&list=PLyve-uz8m19DHjztFJlYPd61fq9qggRTD/");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitFromUrlStringWithHttpProtocol)
	{
		const CHttpUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK_EQUAL(url.GetURL(), "http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.mysite.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK_EQUAL(url.GetPort(), 80);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}

	BOOST_AUTO_TEST_CASE(InitFromUrlStringWithNotDefaultPort)
	{
		const CHttpUrl url("http://www.mysite.com:2000/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK_EQUAL(url.GetURL(), "http://www.mysite.com:2000/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.mysite.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK_EQUAL(url.GetPort(), 2000);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}

	BOOST_AUTO_TEST_CASE(InitFromUrlStringWithoutWWW)
	{
		const CHttpUrl url("https://google.com:666/");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com:666/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "google.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		BOOST_CHECK_EQUAL(url.GetPort(), 666);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(CouldNotInitFromFTPUrl)
	{
		BOOST_CHECK_THROW(CHttpUrl("ftp://google.com:666/"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(CouldNotInitFromStringWithoutDomainAndWWWW)
	{
		BOOST_CHECK_THROW(CHttpUrl("http://..com"), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ConstructorsTestsWithParamsOfUrl)

	BOOST_AUTO_TEST_CASE(InitUrlWithProtocolDomainAndDocument)
	{
		const CHttpUrl url("http", "vk.com", "");
		BOOST_CHECK_EQUAL(url.GetURL(), "http://vk.com/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "vk.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		BOOST_CHECK_EQUAL(url.GetPort(), 80);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithProtocolDomainAndDocumentEndsWithBackslash)
	{
		const CHttpUrl url("https", "www.youtube.com", "/");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://www.youtube.com/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithProtocolDomainPort)
	{
		const CHttpUrl url("https", "www.youtube.com", 666);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://www.youtube.com:666/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		BOOST_CHECK_EQUAL(url.GetPort(), 666);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithProtocolDomain)
	{
		const CHttpUrl url("https", "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://www.youtube.com/");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithProtocolDomainPortDoc)
	{
		const CHttpUrl url("https", "youtube.com", 666, "video-about-muse");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://youtube.com:666/video-about-muse");
		BOOST_CHECK_EQUAL(url.GetDomain(), "youtube.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/video-about-muse");
		BOOST_CHECK_EQUAL(url.GetPort(), 666);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithInvalidDomain)
	{
		BOOST_CHECK_THROW(CHttpUrl("ftp", "youtube.com", 666, "video-about-muse"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithInvalidDoc)
	{
		BOOST_CHECK_THROW(CHttpUrl("http", "ww.youtube.com", 666, "video-about-muse"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithInvalidPort)
	{
		BOOST_CHECK_THROW(CHttpUrl("http", "www.youtube.com", 65536, "video-about-muse"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(InitUrlWithInvalidPort2)
	{
		BOOST_CHECK_THROW(CHttpUrl("http", "www.youtube.com", -1, ""), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(CheckInvalidProtocolMessage)
	{
		try
		{
			CHttpUrl("ftp", "www.youtube.com", 666, "video-about-muse");
		}
		catch (CUrlParsingError& e)
		{
			BOOST_CHECK_EQUAL(e.what(), R"(The URL has invalid protocol: "ftp")");
		}
	}

	BOOST_AUTO_TEST_CASE(CheckInvalidDomainMessage)
	{
		try
		{
			CHttpUrl("http", "ww.youtube.com", 666, "video-about-muse");
		}
		catch (CUrlParsingError& e)
		{
			BOOST_CHECK_EQUAL(e.what(), R"(The URL has invalid domain: "ww.youtube.com")");
		}
	}

	BOOST_AUTO_TEST_CASE(CheckInvalidPortMessage)
	{
		try
		{
			CHttpUrl("http", "www.youtube.com", 65536, "video-about-muse");
		}
		catch (CUrlParsingError& e)
		{
			BOOST_CHECK_EQUAL(e.what(), R"(The URL`s port is out of range: "65536")");
		}
	}

	BOOST_AUTO_TEST_CASE(CheckInvalidPortMessageLowerBound)
	{
		try
		{
			CHttpUrl("http", "www.youtube.com", -1, "video-about-muse");
		}
		catch (CUrlParsingError& e)
		{
			BOOST_CHECK_EQUAL(e.what(), R"(The URL`s port is out of range: "-1")");
		}
	}

BOOST_AUTO_TEST_SUITE_END()