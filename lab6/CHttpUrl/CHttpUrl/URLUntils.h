#pragma once
#include "Protocol.h"
#include <string>

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);
bool IsPortInRange(int port);
Protocol StringProtocolToEnum(std::string protocol);
std::string EnumProtocolToString(Protocol protocol);
int GetDefaultPort(Protocol protocol);
bool IsDomainValid(const std::string& str);
