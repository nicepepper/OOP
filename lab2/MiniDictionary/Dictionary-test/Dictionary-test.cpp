#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch2/catch.hpp"
#include <map>
#include <string>

#include "Dictionary/DictionaryCLI.h"

void InitDictionarys(std::multimap<std::string, std::string>& Dictionary, std::multimap<std::string, std::string>& resultDictionary)
{
	AddNewWordToDictionary("cat", "кошка", Dictionary);
	AddNewWordToDictionary("cat", "киска", Dictionary);
	AddNewWordToDictionary("кот", "cat", Dictionary);
	AddNewWordToDictionary("The Red Square", "Красная Площадь", Dictionary);

	resultDictionary.emplace("cat", "кошка");
	resultDictionary.emplace("cat", "киска");
	resultDictionary.emplace("cat", "кот");
	resultDictionary.emplace("The Red Square", "Красная Площадь");
}

TEST_CASE("DictionaryCLI")
{
	std::multimap<std::string, std::string> Dictionary;
	std::multimap<std::string, std::string> resultDictionary;
	
	//add function
	InitDictionarys(Dictionary, resultDictionary);
	CHECK(Dictionary == resultDictionary);

	//find function
	std::string translation;
	FindWordInDictionary("cat", Dictionary, translation);
	CHECK(translation == "кошка киска кот");

	FindWordInDictionary("CaT", Dictionary, translation);
	CHECK(translation == "кошка киска кот");

	FindWordInDictionary("киска", Dictionary, translation);
	CHECK(translation == "cat");

	FindWordInDictionary("Красная Площадь", Dictionary, translation);
	CHECK(translation == "The Red Square");
	
	// add + find
	translation.clear();
	AddNewWordToDictionary("dog", "", Dictionary);
	FindWordInDictionary("dog", Dictionary, translation);
	CHECK(translation.empty());

	AddNewWordToDictionary("мяч", "ball", Dictionary);
	FindWordInDictionary("мяч", Dictionary, translation);
	CHECK(translation == "ball");

	FindWordInDictionary("ball", Dictionary, translation);
	CHECK(translation == "мяч");
}
