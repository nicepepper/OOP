#pragma once
#include <initializer_list>
#include <iterator>
#include <stdexcept>

// выходит link2019 , попробую внутренний класс описать тут через inline , пока в разработке.

template <class T>
class CMyArray
{
public:
	CMyArray();
	CMyArray(const CMyArray& other);
	CMyArray(const std::initializer_list<T>& list);
	CMyArray(CMyArray&& other) noexcept;
	~CMyArray();

	class CMyArrayIterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
	{
	public:
		CMyArrayIterator(int index, CMyArray<T>& array, bool isReverse);
		CMyArrayIterator(const CMyArrayIterator& other);
		CMyArrayIterator(CMyArrayIterator&& other) noexcept;
		~CMyArrayIterator() = default;

		CMyArrayIterator& operator=(CMyArrayIterator&& other) noexcept;
		CMyArrayIterator& operator=(const CMyArrayIterator& other);
		CMyArrayIterator& operator++();
		CMyArrayIterator operator++(int);
		CMyArrayIterator& operator--();
		CMyArrayIterator operator--(int);

		bool operator==(const CMyArrayIterator& other) const;
		bool operator!=(const CMyArrayIterator& other) const;
		bool operator<(const CMyArrayIterator& other) const;
		bool operator<=(const CMyArrayIterator& other) const;
		bool operator>(const CMyArrayIterator& other) const;
		bool operator>=(const CMyArrayIterator& other) const;

		T& operator*();
		const T& operator*() const;

	private:
		int m_pos;
		CMyArray<T>& m_arr;
		bool m_isReverse;
	};

	CMyArray<T>& operator=(CMyArray<T>&& other) noexcept;
	CMyArray<T>& operator=(const CMyArray<T>& other);

	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;

	CMyArrayIterator begin();
	CMyArrayIterator end();

	CMyArrayIterator rbegin();
	CMyArrayIterator rend();

	void PushBack(T element);
	void Clear();
	void Resize(size_t newSize);
	size_t Size() const;

private:
	T* m_array;
	size_t m_size;
};

template <class T>
CMyArray<T>::CMyArray()
	: m_array(nullptr)
	, m_size(0)
{
}

template <class T>
CMyArray<T>::CMyArray(const CMyArray& other)
	: CMyArray()
{
	Resize(other.m_size);
	for (size_t i = 0; i < m_size; i++)
	{
		m_array[i] = other.m_array[i];
	}
}

template <class T>
CMyArray<T>::CMyArray(const std::initializer_list<T>& list)
	: m_array(nullptr)
	, m_size(0)
{
	for (auto& e : list)
	{
		PushBack(e);
	}
}

template <class T>
CMyArray<T>::CMyArray(CMyArray&& other) noexcept
	: CMyArray()
{
	Clear();
	m_array = other.m_array;
	m_size = other.m_size;
	other.m_array = nullptr;
	other.m_size = 0;
}

template <class T>
CMyArray<T>::~CMyArray()
{
	delete[] m_array;
}

template <class T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T>&& other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	Clear();
	m_array = other.m_array;
	m_size = other.m_size;
	other.m_array = nullptr;
	other.m_size = 0;
	return *this;
}

template <class T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray<T>& other)
{
	if (&other == this)
	{
		return *this;
	}
	Resize(other.m_size);
	for (size_t i = 0; i < m_size; i++)
	{
		m_array[i] = other.m_array[i];
	}
	return *this;
}

template <class T>
T& CMyArray<T>::operator[](size_t pos)
{
	if (pos < m_size)
	{
		return m_array[pos];
	}
	throw std::out_of_range("Array index out of range");
}

template <class T>
const T& CMyArray<T>::operator[](size_t pos) const
{
	if (pos < m_size)
	{
		return m_array[pos];
	}
	throw std::out_of_range("Array index out of range");
}

template <class T>
void CMyArray<T>::PushBack(T element)
{
	Resize(m_size + 1);
	m_array[m_size - 1] = element;
}

template <class T>
void CMyArray<T>::Clear()
{
	delete[] m_array;
	m_array = nullptr;
	m_size = 0;
}

template <class T>
void CMyArray<T>::Resize(size_t newSize)
{
	T* newArray = new T[newSize + 1];
	for (size_t i = 0; i < (newSize > m_size ? m_size : newSize); i++)
	{
		newArray[i] = m_array[i];
	}
	if (newSize > m_size)
	{
		for (size_t i = m_size; i < newSize; i++)
		{
			newArray[i] = {};
		}
	}
	delete[] m_array;
	m_array = newArray;
	m_size = newSize;
}

template <class T>
size_t CMyArray<T>::Size() const
{
	return m_size;
}

template <class T>
CMyArray<T>::CMyArrayIterator::CMyArrayIterator(int index, CMyArray<T>& array, bool isReverse)
	: m_pos(index)
	, m_arr(array)
	, m_isReverse(isReverse)
{
}

template <class T>
CMyArray<T>::CMyArrayIterator::CMyArrayIterator(const CMyArrayIterator& other)
	: m_pos(other.m_pos)
	, m_arr(other.m_arr)
	, m_isReverse(other.m_isReverse)
{
}

template <class T>
CMyArray<T>::CMyArrayIterator::CMyArrayIterator(CMyArrayIterator&& other) noexcept
	: m_pos(other.m_pos)
	, m_arr(other.m_arr)
	, m_isReverse(other.m_isReverse)
{
	*this = std::move(other);
}

template <typename T>
typename CMyArray<T>::CMyArrayIterator& CMyArray<T>::CMyArrayIterator::operator=(CMyArrayIterator&& other) noexcept
{
	*this = std::move(other);
	return *this;
}

template <class T>
typename CMyArray<T>::CMyArrayIterator& CMyArray<T>::CMyArrayIterator::operator=(const CMyArrayIterator& other)
{
	m_pos = other.m_pos;
	m_arr = other.m_arr;
	m_isReverse = other.m_isReverse;

	return *this;
}

template <class T>
typename CMyArray<T>::CMyArrayIterator& CMyArray<T>::CMyArrayIterator::operator++()
{
	if (!m_isReverse && *this == m_arr.end())
	{
		throw std::out_of_range("Incrementing last iterator");
	}
	if (m_isReverse && *this == m_arr.rend())
	{
		throw std::out_of_range("Incrementing last iterator");
	}
	!m_isReverse ? m_pos++ : m_pos--;

	return *this;
}

template <class T>
typename CMyArray<T>::CMyArrayIterator CMyArray<T>::CMyArrayIterator::operator++(int)
{
	auto copy = CMyArrayIterator(*this);
	++this;
	return copy;
}

template <class T>
typename CMyArray<T>::CMyArrayIterator& CMyArray<T>::CMyArrayIterator::operator--()
{
	if (!m_isReverse && *this == m_arr.begin())
	{
		throw std::out_of_range("Decrementing begin iterator");
	}
	if (m_isReverse && *this == m_arr.rbegin())
	{
		throw std::out_of_range("Decrementing begin iterator");
	}
	m_isReverse ? m_pos++ : m_pos--;

	return *this;
}

template <class T>
typename CMyArray<T>::CMyArrayIterator CMyArray<T>::CMyArrayIterator::operator--(int)
{
	auto copy = CMyArrayIterator(*this);
	--this;
	return copy;
}

template <class T>
bool CMyArray<T>::CMyArrayIterator::operator==(const CMyArrayIterator& other) const
{
	return m_pos == other.m_pos;
}

template <class T>
bool CMyArray<T>::CMyArrayIterator::operator!=(const CMyArrayIterator& other) const
{
	return m_pos != other.m_pos;
}

template <class T>
bool CMyArray<T>::CMyArrayIterator::operator<(const CMyArrayIterator& other) const
{
	if (other.m_isReverse != m_isReverse)
	{
		throw std::exception("Comparing iterators of different types");
	}
	return m_isReverse ? m_pos > other.m_pos : m_pos < other.m_pos;
}

template <class T>
bool CMyArray<T>::CMyArrayIterator::operator<=(const CMyArrayIterator& other) const
{
	if (other.m_isReverse != m_isReverse)
	{
		throw std::exception("Comparing iterators of different types");
	}
	return m_isReverse ? m_pos >= other.m_pos : m_pos <= other.m_pos;
}

template <class T>
bool CMyArray<T>::CMyArrayIterator::operator>(const CMyArrayIterator& other) const
{
	return !(*this <= other);
}

template <class T>
bool CMyArray<T>::CMyArrayIterator::operator>=(const CMyArrayIterator& other) const
{
	return !(*this < other);
}

template <class T>
T& CMyArray<T>::CMyArrayIterator::operator*()
{
	return m_arr[size_t(m_pos)];
}

template <class T>
const T& CMyArray<T>::CMyArrayIterator::operator*() const
{
	return m_arr[size_t(m_pos)];
}

template <class T>
typename CMyArray<T>::CMyArrayIterator CMyArray<T>::begin()
{
	return CMyArray<T>::CMyArrayIterator(0, *this, false);
}

template <class T>
typename CMyArray<T>::CMyArrayIterator CMyArray<T>::end()
{
	return CMyArray<T>::CMyArrayIterator(m_size, *this, false);
}

template <class T>
typename CMyArray<T>::CMyArrayIterator CMyArray<T>::rbegin()
{
	return CMyArray<T>::CMyArrayIterator(m_size - 1, *this, true);
}

template <class T>
typename CMyArray<T>::CMyArrayIterator CMyArray<T>::rend()
{
	return CMyArray<T>::CMyArrayIterator(-1, *this, true);
}