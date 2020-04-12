#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <algorithm>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	UNKNOWN
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);
