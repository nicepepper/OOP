#pragma once
#include <string>

struct StringListNode
{
	StringListNode(std::string str, StringListNode* prev, StringListNode* next)
		: str(std::move(str))
		, prev(prev)
		, next(next)
	{
	}
	std::string str;
	StringListNode* prev;
	StringListNode* next;
};