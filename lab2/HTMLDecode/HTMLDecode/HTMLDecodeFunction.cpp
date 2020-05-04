#include "HTMLDecodeFunction.h"

const std::string FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS = "&";
const std::vector < std::pair <std::string, std::string>> HTML_ENTITIES {
	{ "&apos;", "\'" },
	{ "&quot;", "\"" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

std::string HTMLDecode(const std::string& html)
{
	std::string result;
	size_t pos = 0;
	while (pos < html.length())
	{
		size_t foundPos = html.find(FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS, pos);
		result.append(html, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			const auto itEntity = std::find_if(HTML_ENTITIES.cbegin(), HTML_ENTITIES.cend(),
				[&html, foundPos](const std::pair<std::string, std::string>& entity) {
					return html.compare(foundPos, entity.first.length(), entity.first) == 0;
				});
			if (itEntity != HTML_ENTITIES.cend())
			{
				result.append(itEntity->second);
				foundPos += itEntity->first.length();
			}
			else
			{
				result.append(FIRST_SYMBOL_OF_ENCODED_HTML_SYMBOLS);
				++foundPos;
			}
		}
		pos = foundPos;
	}
	return result;
}
