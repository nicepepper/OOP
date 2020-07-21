#pragma once
#include "StringListNode.h"
#include <stdexcept>
#include <iterator>

class CStringListIterator : public std::iterator<std::bidirectional_iterator_tag, StringListNode>
{
public:
	CStringListIterator(StringListNode* node, StringListNode* begin, StringListNode* end, bool isReverse);
	CStringListIterator(const CStringListIterator&);
	CStringListIterator(CStringListIterator&&) noexcept;
	~CStringListIterator() = default;

	CStringListIterator& operator=(CStringListIterator&&) noexcept;
	CStringListIterator& operator=(const CStringListIterator&);
	
	CStringListIterator& operator++();
	CStringListIterator operator++(int);

	CStringListIterator& operator--();
	CStringListIterator operator--(int);

	bool operator!=(const CStringListIterator& other) const;
	bool operator==(const CStringListIterator& other) const;

	std::string& operator*();
	const std::string& operator*() const;

private:
	friend class CStringList;
	StringListNode* m_node;
	StringListNode* m_begin;
	StringListNode* m_end;
	bool m_isReverse;
};