#include "HTMLDecodeFunction.h"
#include <vector>

constexpr char NOT_FOUND_SYMBOL = '\n';

char GetSymbolToHTMLEntity(const std::string& str)
{
	return (str == APOSTROPHE_ENCODED) ? APOSTROPHE : (str == QUATATION_MARK_ENCODED) ? QUATATION_MARK : (str == LESS_THAN_SIGN_ENCODED) ? LESS_THAN_SIGN : (str == GREATER_THAN_SIGN_ENCODED) ? GREATER_THAN_SIGN : (str == AMPERSAND_ENCODED) ? AMPERSAND : NOT_FOUND_SYMBOL;
}

std::string HTMLDecode(std::string const& html)
{
	std::string resultStr;
	std::string EncodedString;
	bool comparisonStart = false;
	char decodedSymbol;

	for (const char ch : html)
	{
		if (ch == FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS)
		{
			comparisonStart = true;

			if (!EncodedString.empty())
			{
				resultStr += EncodedString;
				EncodedString.clear();
			}
		}

		if (comparisonStart)
		{
			EncodedString += ch;
		}
		else
		{
			resultStr += ch;
		}

		if (comparisonStart && (ch == LAST_SYMBOL_OF_ENCODED_HTML_SYMBOLS))
		{
			comparisonStart = false;

			decodedSymbol = GetSymbolToHTMLEntity(EncodedString);

			if (decodedSymbol != NOT_FOUND_SYMBOL)
			{
				resultStr += decodedSymbol;
			}
			else
			{
				resultStr += EncodedString;
			}

			EncodedString.clear();
		}
	}

	return resultStr;
}
