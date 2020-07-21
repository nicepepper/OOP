#include "CStringListIterator.h"

CStringListIterator::CStringListIterator(StringListNode* node, StringListNode* begin, StringListNode* end, const bool isReverse)
	: m_node(node)
	, m_begin(begin)
	, m_end(end)
	, m_isReverse(isReverse)
{
}

CStringListIterator::CStringListIterator(const CStringListIterator& iterator)
{
	m_node = iterator.m_node;
	m_begin = iterator.m_begin;
	m_end = iterator.m_end;
	m_isReverse = iterator.m_isReverse;
}

CStringListIterator::CStringListIterator(CStringListIterator&& iterator) noexcept
{
	m_node = iterator.m_node;
	m_begin = iterator.m_begin;
	m_end = iterator.m_end;
	m_isReverse = iterator.m_isReverse;

	iterator.m_node = nullptr;
	iterator.m_begin = nullptr;
	iterator.m_end = nullptr;
}

CStringListIterator& CStringListIterator::operator=(CStringListIterator&& iterator) noexcept
{
	m_node = iterator.m_node;
	m_begin = iterator.m_begin;
	m_end = iterator.m_end;
	m_isReverse = iterator.m_isReverse;

	iterator.m_node = nullptr;
	iterator.m_begin = nullptr;
	iterator.m_end = nullptr;

	return *this;
}

CStringListIterator& CStringListIterator::operator=(const CStringListIterator& iterator)
{
	m_node = iterator.m_node;
	m_begin = iterator.m_begin;
	m_end = iterator.m_end;
	m_isReverse = iterator.m_isReverse;

	return *this;
}

CStringListIterator& CStringListIterator::operator++()
{
	if (m_node == m_end || m_node == nullptr || (m_isReverse ? !m_node->prev : !m_node->next))
	{
		throw std::runtime_error("Getting out of the list range");
	}
	m_isReverse ? m_node = m_node->prev : m_node = m_node->next;

	return *this;
}

CStringListIterator CStringListIterator::operator++(int)
{
	CStringListIterator copy = *this;
	++*this;

	return copy;
}

CStringListIterator CStringListIterator::operator--(int)
{
	CStringListIterator copy = *this;
	--*this;

	return copy;
}

CStringListIterator& CStringListIterator::operator--()
{
	if (m_node == m_begin || m_node == nullptr
		|| (m_isReverse ? !m_node->next : !m_node->prev)
		|| m_node->prev == m_begin
		|| (m_isReverse ? m_node->next == m_begin : false))
	{
		throw std::runtime_error("Getting out of the list range");
	}
	m_isReverse ? m_node = m_node->next : m_node = m_node->prev;

	return *this;
}

std::string& CStringListIterator::operator*()
{
	if (!m_node || m_node == m_end || m_node == m_begin)
	{
		throw std::runtime_error("Access to undefined value");
	}

	return m_node->str;
}

const std::string& CStringListIterator::operator*() const
{
	if (!m_node || m_node == m_end || m_node == m_begin)
	{
		throw std::runtime_error("Access to undefined value");
	}

	return m_node->str;
}

bool CStringListIterator::operator!=(const CStringListIterator& other) const
{
	return m_node != other.m_node;
}

bool CStringListIterator::operator==(const CStringListIterator& other) const
{
	return m_node == other.m_node;
}