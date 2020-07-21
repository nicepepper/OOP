#include "CStringList.h"

CStringList::CStringList()
	: m_size(0)
	, m_firstNode(nullptr)
	, m_lastNode(nullptr)
	, m_begin(nullptr)
	, m_end(nullptr)
{
	try
	{
		m_begin = new StringListNode(std::string(), nullptr, nullptr);
		m_end = new StringListNode(std::string(), nullptr, nullptr);
	}
	catch (std::exception&)
	{
		delete m_begin;
		delete m_end;
	}
}

CStringList::CStringList(const std::initializer_list<std::string>& list)
	: CStringList()
{
	for (auto& str : list)
	{
		PushBack(str);
	}
}

CStringList::~CStringList()
{
	delete m_begin;
	delete m_end;
	Clear();
}

void CStringList::Clear()
{
	StringListNode* node = m_firstNode;
	while (node != nullptr && node != m_end)
	{
		StringListNode* nextNode = node->next;
		delete node;
		node = nextNode;
	}
	m_firstNode = nullptr;
	m_lastNode = nullptr;
	m_size = 0;
}

size_t CStringList::Size() const
{
	return m_size;
}

void CStringList::PushBack(const std::string& str)
{
	StringListNode* node = new StringListNode(str, m_lastNode, nullptr);
	node->next = m_end;
	m_end->prev = node;
	if (m_size == 0)
	{
		m_firstNode = node;
		node->prev = m_begin;
		m_begin->next = node;
	}
	else if (m_lastNode)
	{
		m_lastNode->next = node;
	}
	m_lastNode = node;
	m_size++;
}

void CStringList::PushFront(const std::string& str)
{
	StringListNode* node = new StringListNode(str, nullptr, m_firstNode);
	node->prev = m_begin;
	m_begin->next = node;
	if (m_size == 0)
	{
		m_lastNode = node;
		node->next = m_end;
		m_end->prev = node;
	}
	else if (m_firstNode)
	{
		m_firstNode->prev = node;
	}
	m_firstNode = node;
	m_size++;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::Insert(CStringListIterator&& iterator, const std::string& str)
{
	CStringListIterator iter(iterator);
	Insert(iter, str);
}

void CStringList::Insert(CStringListIterator& iterator, const std::string& str)
{
	if (iterator == begin() || iterator == rend())
	{
		PushFront(str);
		return;
	}
	if (iterator == end() || m_lastNode == nullptr)
	{
		PushBack(str);
		return;
	}
	StringListNode* node = new StringListNode(str, iterator.m_node->prev, iterator.m_node);
	if (iterator.m_node->prev)
	{
		iterator.m_node->prev->next = node;
	}
	iterator.m_node->prev = node;
	++m_size;
}

void CStringList::Erase(CStringListIterator&& iterator)
{
	CStringListIterator iter = std::move(iterator);
	Erase(iter);
}

void CStringList::Erase(CStringListIterator& iterator)
{
	if (!iterator.m_node || iterator.m_node == m_end || iterator.m_node == m_begin)
	{
		throw std::runtime_error("An attempt to erase not allocated memory was caught");
	}
	StringListNode* prevNode = iterator.m_node->prev;
	StringListNode* nextNode = iterator.m_node->next;
	if (iterator == begin())
	{
		m_firstNode = nextNode;
		nextNode->prev = m_begin;
	}
	else
	{
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	}
	delete iterator.m_node;
	iterator.m_node = nullptr;
	m_size--;
}

CStringListIterator CStringList::begin()
{
	return CStringListIterator(m_firstNode, m_begin, m_end, false);
}

CStringListIterator CStringList::end()
{
	return CStringListIterator(m_end, m_begin, m_end, false);
}

const CStringListIterator CStringList::cbegin() const
{
	return CStringListIterator(m_firstNode, m_begin, m_end, false);
}

const CStringListIterator CStringList::cend() const
{
	return CStringListIterator(m_end, m_begin, m_end, false);
}

CStringListIterator CStringList::rbegin()
{
	return CStringListIterator(m_lastNode, m_end, m_begin, true);
}

CStringListIterator CStringList::rend()
{
	return CStringListIterator(m_begin, m_end, m_begin, true);
}

const CStringListIterator CStringList::crbegin() const
{
	return CStringListIterator(m_lastNode, m_end, m_begin, true);
}

const CStringListIterator CStringList::crend() const
{
	return CStringListIterator(m_begin, m_end, m_begin, true);
}