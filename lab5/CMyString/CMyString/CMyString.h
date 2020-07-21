#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);
	~CMyString();

	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;

	CMyString operator+(const CMyString& str) const;
	friend CMyString operator+(const CMyString& str, char ch);

	CMyString& operator+=(const CMyString& str);
	CMyString operator+=(char ch);

	char& operator[](const size_t pos);
	const char& operator[](const size_t pos) const;

	bool operator==(const CMyString& str) const;
	bool operator!=(const CMyString& str) const;
	bool operator<(const CMyString& str) const;
	bool operator>(const CMyString& str) const;
	bool operator<=(const CMyString& str) const;
	bool operator>=(const CMyString& str) const;

	friend std::ostream& operator<<(std::ostream& out, const CMyString& str);
	friend std::istream& operator>>(std::istream& in, CMyString& str);

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(const size_t start, const size_t length = SIZE_MAX) const;
	void Clear();

private:
	void AllocateMemoryAndProcessCopyingOfOldData(size_t sizeOfMemory, bool isNeedToCopyTheOldString);
	char* m_str;
	size_t m_length;
};
