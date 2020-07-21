#include "CHttpUrl.h"
#include <iostream>
#include <string>

int main()
{
	std::string inStr;
	while (std::getline(std::cin, inStr))
	{
		try
		{
			CHttpUrl url(inStr);
			const auto protocol = url.GetProtocol() == Protocol::HTTP ? "http" : "https";
			std::cout << ">   URL: " << url.GetURL() << std::endl;
			std::cout << ">   Protocol: " << protocol << std::endl;
			std::cout << ">   Domain: " << url.GetDomain() << std::endl;
			std::cout << ">   Port: " << url.GetPort() << std::endl;
			std::cout << ">   Document: " << url.GetDocument() << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}
