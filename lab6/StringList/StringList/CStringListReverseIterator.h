#pragma once
#include "CStringListIterator.h"

class CStringListReverseIterator : CStringListIterator
{
public:
	CStringListReverseIterator(StringListNode* node, StringListNode* begin, StringListNode* end);
	CStringListReverseIterator(CStringListReverseIterator&&) = default;
	CStringListReverseIterator(const CStringListReverseIterator&) = default;
	~CStringListReverseIterator() = default;

	CStringListReverseIterator& operator=(CStringListReverseIterator&&) noexcept;
	CStringListReverseIterator& operator=(const CStringListReverseIterator&);
	CStringListReverseIterator& operator++();
	CStringListReverseIterator operator++(int);
	CStringListReverseIterator& operator--();
	CStringListReverseIterator operator--(int);
};