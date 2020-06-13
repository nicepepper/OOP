#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch2/catch.hpp"

#include "ParseURL/ParseURL.h"


TEST_CASE("ParseURL - test")
{
	SECTION("test - https://google.com/")
	{
		const std::string url = "https://google.com/";
		std::string host, document;
		int port;
		Protocol protocol;
		bool success = ParseURL(url, protocol, port, host, document);
		CHECK(success);
		CHECK(protocol == Protocol::HTTPS);
		CHECK(host == "google.com");
		CHECK(port == 443);
		CHECK(document == "");
	}

	SECTION("mysite_test - http")
	{
		const std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		std::string host, document;
		int port;
		Protocol protocol;
		bool success = ParseURL(url, protocol, port, host, document);
		CHECK(success);
		CHECK(protocol == Protocol::HTTP);
		CHECK(host == "www.mysite.com");
		CHECK(port == 80);
		CHECK(document == "docs/document1.html?page=30&lang=en#title");
	}

	SECTION("https - 443")
	{
		const std::string url = "https://www.stackoverflow.com/questions/27745/getting-parts-of-a-url-regex";
		std::string host, document;
		int port;
		Protocol protocol;
		bool success = ParseURL(url, protocol, port, host, document);
		CHECK(success);
		CHECK(protocol == Protocol::HTTPS);
		CHECK(host == "www.stackoverflow.com");
		CHECK(port == 443);
		CHECK(document == "questions/27745/getting-parts-of-a-url-regex");
	}

	SECTION("ftp - 21")
	{
		const std::string url = "FTP://www.onedrive.live.com";
		std::string host, document;
		int port;
		Protocol protocol;
		bool success = ParseURL(url, protocol, port, host, document);
		CHECK(success);
		CHECK(protocol == Protocol::FTP);
		CHECK(host == "www.onedrive.live.com");
		CHECK(port == 21);
		CHECK(document == "");
	}

	SECTION("ftp - 2000")
	{
		const std::string url = "FTP://www.onedrive.live.com:2000/";
		std::string host, document;
		int port;
		Protocol protocol;
		bool success = ParseURL(url, protocol, port, host, document);
		CHECK(success);
		CHECK(protocol == Protocol::FTP);
		CHECK(host == "www.onedrive.live.com");
		CHECK(port == 2000);
		CHECK(document == "");
	}
}
