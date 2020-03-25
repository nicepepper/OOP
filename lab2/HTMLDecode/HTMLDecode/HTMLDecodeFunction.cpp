#include "HTMLDecodeFunction.h"


constexpr char NOT_FOUND_SYMBOL = '\n';

char EncodedSymbolToDecoded(const std::string& str)
{
	return
		(str == APOSTROPHE_ENCODED) ? APOSTROPHE :
		(str == QUATATION_MARK_ENCODED) ? QUATATION_MARK :
		(str == LESS_THAN_SIGN_ENCODED) ? LESS_THAN_SIGN :
		(str == GREATER_THAN_SIGN_ENCODED) ? GREATER_THAN_SIGN :
		(str == AMPERSAND_ENCODED) ? AMPERSAND : NOT_FOUND_SYMBOL;
}

void SearhcTheStartOfSpecialSymbol(std::string& resultStr, std::string& foundEncodedString, const char ch, bool& comparisonStart)
{
	if (ch == FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS)
	{
		comparisonStart = true;
		
		if (!foundEncodedString.empty())
		{
			resultStr += foundEncodedString;
			foundEncodedString.clear();
		}
	}
}

void ComparisonProcessing(std::string& resultStr, std::string& foundEncodedString,const char ch, bool comparisonStart)
{
	if (comparisonStart)
	{
		foundEncodedString += ch;
	}
	else
	{
		resultStr += ch;
	}
}

void SearhcTheEndOfSpecialSymbol(std::string& resultStr, std::string& foundEncodedString,const char ch, bool& comparisonStart)
{
	if (comparisonStart && (ch == LAST_SYMBOL_OF_ENCODED_HTML_SYMBOLS))
	{
		comparisonStart = false;

		char decodedSymbol = EncodedSymbolToDecoded(foundEncodedString);

		if (decodedSymbol != NOT_FOUND_SYMBOL)
		{
			resultStr += decodedSymbol;
		}
		else
		{
			resultStr += foundEncodedString;
		}

		foundEncodedString.clear();
	}
}

std::string HTMLDecode(std::string const& html)
{
	std::string resultStr;
	std::string foundEncodedString;
	bool comparisonStart = false;

	for (const char ch : html)
	{
		SearhcTheStartOfSpecialSymbol(resultStr, foundEncodedString, ch, comparisonStart);
		ComparisonProcessing(resultStr, foundEncodedString, ch, comparisonStart);
		SearhcTheEndOfSpecialSymbol(resultStr, foundEncodedString, ch, comparisonStart);
	}

	return resultStr;
}
