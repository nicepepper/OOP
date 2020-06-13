// ParseURL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ParseURL.h"
#include <iostream>

int main() // Напишите критерии, или укажите где вазять информацию по url. Не знал что брать, читал про (RFC 3986) и видел регулярку, но не стал испоьзовать
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	std::string inputString;
	std::cout << "Enter the URL you want to process: ";
	std::cin >> inputString;
	if (ParseURL(inputString, protocol, port, host, document))
	{
		std::cout << inputString << std::endl;
		std::cout << "HOST: " << host << std::endl;
		std::cout << "PORT: " << port << std::endl;
		std::cout << "DOC: " << document << std::endl;
	}
	else
	{
		std::cout << "Error, this URL is not valid!" << std::endl;
	}
	return 0;
}
