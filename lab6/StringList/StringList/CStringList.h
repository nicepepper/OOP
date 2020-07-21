#pragma once
#include "CStringListIterator.h"
#include "StringListNode.h"
#include <initializer_list>
#include <string>

class CStringList
{
public:
	friend class CStringListIterator;
	CStringList();
	CStringList(const std::initializer_list<std::string>& l);
	~CStringList();
	void Clear();
	
	size_t Size() const;
	
	void PushBack(const std::string& str);
	void PushFront(const std::string& str);
	
	bool IsEmpty() const;
	
	void Insert(CStringListIterator& iterator, const std::string& str);
	void Insert(CStringListIterator&& iterator, const std::string& str);
	
	void Erase(CStringListIterator& iterator);
	void Erase(CStringListIterator&& iterator);

	CStringListIterator begin();
	CStringListIterator end();

	const CStringListIterator cbegin() const;
	const CStringListIterator cend() const;

	CStringListIterator rbegin();
	CStringListIterator rend();

	const CStringListIterator crbegin() const;
	const CStringListIterator crend() const;

private:
	size_t m_size;
	StringListNode* m_firstNode;
	StringListNode* m_lastNode;
	StringListNode* m_begin;
	StringListNode* m_end;
};