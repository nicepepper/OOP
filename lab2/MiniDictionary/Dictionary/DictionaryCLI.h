#pragma once
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

void DictionaryCLI(const std::string& fileName);
void AddNewWordToDictionary(const std::string& word, const std::string& translation, std::multimap<std::string, std::string>& Dictionary);
void FindWordInDictionary(const std::string& inputStr,const std::multimap<std::string, std::string>& Dictionary, std::string& outputStr);
