#include "CStringListReverseIterator.h"

CStringListReverseIterator::CStringListReverseIterator(StringListNode* node, StringListNode* begin, StringListNode* end)
	: CStringListIterator(node, begin, end, false)
{
}

CStringListReverseIterator& CStringListReverseIterator::operator++()
{
	CStringListIterator::operator--();

	return *this;
}

CStringListReverseIterator CStringListReverseIterator::operator++(int)
{
	auto obj(*this);
	CStringListIterator::operator--();

	return obj;
}

CStringListReverseIterator& CStringListReverseIterator::operator--()
{
	CStringListIterator::operator++();

	return *this;
}

CStringListReverseIterator CStringListReverseIterator::operator--(int)
{
	auto obj(*this);
	CStringListIterator::operator++();

	return obj;
}

CStringListReverseIterator& CStringListReverseIterator::operator=(CStringListReverseIterator&& it) noexcept
{
	*this = std::move(it);

	return *this;
}

CStringListReverseIterator& CStringListReverseIterator::operator=(const CStringListReverseIterator& it)
{
	const CStringListReverseIterator iterator(it);
	*this = iterator;

	return *this;
}