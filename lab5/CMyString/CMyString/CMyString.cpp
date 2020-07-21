#include "CMyString.h"

const char* EMPTY_C_STRING = "";

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_str, other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString()
{
	*this = std::move(other);
}

CMyString::~CMyString()
{
	delete[] m_str;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	delete[] m_str;

	m_str = other.m_str;
	m_length = other.m_length;

	other.m_str = nullptr;
	other.m_length = 0;

	return *this;
}

CMyString::CMyString()
	: m_str(nullptr)
	, m_length(0)
{
}

CMyString::CMyString(const char* pString, const size_t length)
	: CMyString()
{
	if (length > 0)
	{
		AllocateMemoryAndProcessCopyingOfOldData(length, false);
		if (m_str)
		{
			std::memcpy(m_str, pString, length);
		}
	}
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this == &other)
	{
		return *this;
	}
	AllocateMemoryAndProcessCopyingOfOldData(other.GetLength(), false);
	std::memcpy(m_str, other.m_str, other.GetLength());
	return *this;
}

void CMyString::AllocateMemoryAndProcessCopyingOfOldData(size_t sizeOfMemory, bool isNeedToCopyTheOldString)
{
	if ((isNeedToCopyTheOldString) && (m_length > sizeOfMemory))
	{
		throw std::exception("Previous string is much longer than allocated memory");
	}
	char* newStr = new char[sizeOfMemory + 1];
	if (isNeedToCopyTheOldString)
	{
		std::memcpy(newStr, m_str, m_length);
	}
	else
	{
		m_length = 1;
	}
	delete[] m_str;
	m_str = newStr;
	m_str[sizeOfMemory] = '\0';
	m_length = sizeOfMemory + 1;
}

CMyString& CMyString::operator+=(const CMyString& str)
{
	if (str.GetLength() == 0)
	{
		return *this;
	}

	const size_t oldLength = GetLength();
	const size_t copyStrLength = str.GetLength();
	AllocateMemoryAndProcessCopyingOfOldData(GetLength() + str.GetLength(), true);
	if (m_str && str.m_str)
	{
		std::memcpy(m_str + oldLength, str.m_str, copyStrLength);
	}
	return *this;
}

CMyString CMyString::operator+=(char ch)
{
	AllocateMemoryAndProcessCopyingOfOldData(GetLength() + 1, true);
	m_str[GetLength() - 1] = ch;
	return *this;
}

CMyString CMyString::operator+(const CMyString& str) const
{
	CMyString strCopy(*this);
	strCopy += str;
	return strCopy;
}

CMyString operator+(const CMyString& str, char ch)
{
	auto strCopy = CMyString(str);
	strCopy += ch;
	return strCopy;
}

std::ostream& operator<<(std::ostream& out, const CMyString& str)
{
	for (size_t i = 0; i < str.GetLength(); i++)
	{
		out << str.m_str[i];
	}
	return out;
}

std::istream& operator>>(std::istream& in, CMyString& str)
{
	std::string inStr;
	in >> inStr;
	str = CMyString(inStr);
	return in;
}

const char* CMyString::GetStringData() const
{
	return m_str ? m_str : EMPTY_C_STRING;
}

size_t CMyString::GetLength() const
{
	return m_str ? m_length - 1 : 0;
}

void CMyString::Clear()
{
	delete[] m_str;
	m_str = nullptr;
	m_length = 0;
}

char& CMyString::operator[](const size_t pos)
{
	if ((pos >= GetLength()))
	{
		throw std::out_of_range("Index out of string range");
	}
	return m_str[pos];
}

const char& CMyString::operator[](const size_t pos) const
{
	if ((pos >= GetLength()))
	{
		throw std::out_of_range("Index out of string range");
	}
	return m_str[pos];
}

bool CMyString::operator==(const CMyString& str) const
{
	if (GetLength() != str.GetLength())
	{
		return false;
	}
	for (size_t i = 0; i < GetLength(); i++)
	{
		if (str[i] != (*this)[i])
		{
			return false;
		}
	}
	return true;
}

bool CMyString::operator!=(const CMyString& str) const
{
	return !(str == (*this));
}

bool CMyString::operator<(const CMyString& str) const
{
	for (size_t i = 0; i < std::min(str.GetLength(), GetLength()); i++)
	{
		if ((*this)[i] > str[i])
		{
			return false;
		}

		if ((*this)[i] < str[i])
		{
			return true;
		}
	}
	return GetLength() < str.GetLength();
}

bool CMyString::operator>(const CMyString& str) const
{
	return (str < (*this));
}

bool CMyString::operator<=(const CMyString& str) const
{
	return !(str < (*this));
}

bool CMyString::operator>=(const CMyString& str) const
{
	return !((*this) < str);
}

CMyString CMyString::SubString(const size_t start, const size_t length) const
{
	if (start > GetLength() - 1)
	{
		throw std::out_of_range("Start position is out of range");
	}
	const size_t end = std::min(length, GetLength() - start);
	return CMyString(&m_str[start], end);
}
