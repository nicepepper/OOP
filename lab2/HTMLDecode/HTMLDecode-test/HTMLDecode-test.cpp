#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "..\catch2\catch.hpp"
#include "HTMLDecode/HTMLDecodeFunction.h"
#include <string>

TEST_CASE(" HTMLDecode - decoding html HTML entity ")
{
	//empty_string
	std::string emptyString;
	std::string result = HTMLDecode(emptyString);
	CHECK(result.empty());

	//decode_quot
	std::string quotEncode = "&quot&quot;";
	std::string quotDecode = "&quot\"";
	result = HTMLDecode(quotEncode);
	CHECK(result == quotDecode);

	//decode_string
	std::string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string str = "Cat <says> \"Meow\". M&M's";
	result = HTMLDecode(html);
	CHECK(result == str);

	//decode_amp
	std::string amp = "&lt;";
	result = HTMLDecode("&amp;lt;");
	CHECK(result == amp);

	//decode_many_amp
	std::string manyAmp = "&&&&&&&";
	std::string apos = "&amp;&amp;&amp;&amp;&amp;&amp;&amp;";
	result = HTMLDecode(apos);
	CHECK(result == manyAmp);
}
