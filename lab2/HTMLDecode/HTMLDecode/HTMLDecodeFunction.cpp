#include "HTMLDecodeFunction.h"

constexpr char FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS = '&';
constexpr char LAST_SYMBOL_OF_ENCODED_HTML_SYMBOLS = ';';

const std::vector<std::pair<std::string, char>> HTML_ENTITIES{
	{ "&apos;", '\'' },
	{ "&quot;", '\"' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};

char GetSymbolHTMLEntities(const std::string& entityHTML)
{
	auto it = std::find_if(HTML_ENTITIES.begin(), HTML_ENTITIES.end(),
		[&entityHTML](const std::pair<std::string, char>& element) { return element.first == entityHTML; });
	if (it == HTML_ENTITIES.end())
	{
		return '0';
	}
	return it->second;
}

std::string FindHTMLEntityInSubstring(const std::string& html, const size_t itPosStart, const size_t itposEnd)
{
	std::string subStr = html.substr(itPosStart, itposEnd - itPosStart + 1);
	auto it = std::find_if(HTML_ENTITIES.begin(), HTML_ENTITIES.end(),
		[&subStr](const std::pair<std::string, char>& element) { return element.first == subStr; });
	if (it == HTML_ENTITIES.end())
	{
		return "";
	}
	return it->first;
}

void DiscardFlags(bool& isFoundStartSymbol, bool& isFoundEndSymbol)
{
	isFoundStartSymbol = false;
	isFoundEndSymbol = false;
}

std::string HTMLDecode(std::string& html)
{
	bool isFoundStartSymbol = false;
	bool isFoundEndSymbol = false;
	size_t itPosStart = 0;
	size_t itPosEnd = 0;
	for (auto it = html.begin(); it != html.end(); ++it)
	{
		if (*it == FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS)
		{
			isFoundStartSymbol = true;
			itPosStart = it - html.begin();
		}

		if (*it == LAST_SYMBOL_OF_ENCODED_HTML_SYMBOLS)
		{
			isFoundEndSymbol = true;
			itPosEnd = it - html.begin();
		}

		if (isFoundStartSymbol && isFoundEndSymbol)
		{
			if (itPosStart > itPosEnd)
			{
				DiscardFlags(isFoundStartSymbol, isFoundEndSymbol);
			}
			else
			{
				auto entityHTML = FindHTMLEntityInSubstring(html, itPosStart, itPosEnd);
				if (!entityHTML.empty())
				{
					std::cout << html.substr(itPosStart + 1, itPosEnd - itPosStart + 1);
					//html.erase(itPosStart + 1, itPosEnd - itPosStart + 1);
					//html.at(itPosStart) = GetSymbolHTMLEntities(entityHTML);
					//DiscardFlags(isFoundStartSymbol, isFoundEndSymbol);
				}
				else
				{
					DiscardFlags(isFoundStartSymbol, isFoundEndSymbol);
				}
			}
		}
	}
	return html;
}
