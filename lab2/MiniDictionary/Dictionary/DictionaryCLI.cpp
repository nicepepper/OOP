#include "DictionaryCLI.h"

constexpr char WORD_BORDER_LEFT = '{';
constexpr char WORD_BORDER_RIGHT = '}';
const std::string DIALOG_EXIT_KEY = "...";

void Trim(std::string& str)
{
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
}

void ParseDictionaryDataString(const std::string& currentStr, std::pair<std::string, std::string>& wordAndItsTranslation)
{
	bool firstWord = false;
	bool secondWord = false;

	for (size_t i = 0; i < currentStr.size(); i++)
	{
		if (currentStr.at(i) == WORD_BORDER_LEFT)
		{
			if (!firstWord)
			{
				firstWord = true;
			}
			else
			{
				secondWord = true;
			}
			continue;
		}

		if (firstWord && !secondWord && currentStr.at(i) != WORD_BORDER_RIGHT)
		{
			wordAndItsTranslation.first += currentStr.at(i);
		}

		if (secondWord && currentStr.at(i) != WORD_BORDER_RIGHT)
		{
			wordAndItsTranslation.second += currentStr.at(i);
		}
	}
}

void DictionaryInitialization(const std::string& fileName, std::multimap<std::string, std::string>& Dictionary)
{
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << fileName << "' for reading\n"
				  << "The dictionary will be empty" << std::endl;
		input.close();
		return;
	}
	std::string currentStr;
	std::pair<std::string, std::string> wordAndItsTranslation;
	while (std::getline(input, currentStr))
	{
		wordAndItsTranslation.first = "";
		wordAndItsTranslation.second = "";
		ParseDictionaryDataString(currentStr, wordAndItsTranslation);
		Dictionary.emplace(wordAndItsTranslation); //emplace или insert? insert создает копию, emlace вставляет на "месте" - не нарушает ли он порядок в бинарном дереве, проводится ли в дереве балансровка на этапе добавления??
	}
	input.close();
}

bool IsLineInEnglish(const std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isalpha(str.at(i)) && !std::isblank(str.at(i)))
		{
			return false;
		}
	}
	return true;
}

void FindWordTranslation(const std::string& wordStr, const std::multimap<std::string, std::string>& Dictionary, std::string& translationsStr)
{
	translationsStr.clear();
	std::string lowercaseWord = wordStr;
	std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), tolower);
	auto rangeOfTranslations = Dictionary.equal_range(lowercaseWord);
	for (auto it = rangeOfTranslations.first; it != rangeOfTranslations.second; ++it)
	{
		translationsStr.append(it->second + " ");
	}
	Trim(translationsStr);
}

void FindWordByTranslation(const std::string& translationStr, const std::multimap<std::string, std::string>& Dictionary, std::string& wordStr)
{
	wordStr.clear();
	std::string lowercaseTranslation = translationStr;
	std::transform(lowercaseTranslation.begin(), lowercaseTranslation.end(), lowercaseTranslation.begin(), tolower);
	auto equalValues = [&](const std::pair<std::string, std::string> pair) {
		return pair.second == lowercaseTranslation;
	};
	wordStr = std::find_if(Dictionary.begin(), Dictionary.end(), equalValues)->first;
}

void FindWordInDictionary(const std::string& inputStr, const std::multimap<std::string, std::string>& Dictionary, std::string& outputStr)
{
	if (IsLineInEnglish(inputStr))
	{
		FindWordTranslation(inputStr, Dictionary, outputStr);
	}
	else
	{
		FindWordByTranslation(inputStr, Dictionary, outputStr);
	}
}

void OutputStringToStream(const std::string& str, std::ostream& output)
{
	output << str << std::endl;
}

void InputStreamToString(std::istream& in, std::string& str)
{
	std::cout << '>';
	std::getline(std::cin, str);
	Trim(str);
}

void AddNewWordAndTranslationToDictionary(const std::string& word, const std::string& translation, std::multimap<std::string, std::string>& Dictionary)
{
	Dictionary.emplace(word, translation);
	std::cout << "The word \"" << word << "\" is stored in the dictionary as \"" << translation << "\"." << std::endl;
}

void AddNewWordToDictionary(const std::string& word, const std::string& translation, std::multimap<std::string, std::string>& Dictionary)
{
	if (!word.empty() && !translation.empty())
	{
		if (IsLineInEnglish(word))
		{
			AddNewWordAndTranslationToDictionary(word, translation, Dictionary);
		}
		else
		{
			AddNewWordAndTranslationToDictionary(translation, word, Dictionary);
		}
	}
	
}

void HandleAddingWordToDictionary(const std::string word, std::multimap<std::string, std::string>& Dictionary)
{
	std::string translation;
	std::cout << "Unknown word \"" << word << "\". Enter a translation or blank line to refuse." << std::endl;
	InputStreamToString(std::cin, translation);
	if (translation.empty())
	{
		std::cout << "The word \"" << word << "\" is ignored." << std::endl;
		return;
	}
	AddNewWordToDictionary(word, translation, Dictionary);
}

void ProcessDictionary(std::multimap<std::string, std::string>& Dictionary)
{
	std::string inputString;
	std::string outputString;
	do
	{
		InputStreamToString(std::cin, inputString);
		if (inputString.empty())
		{
			std::cout << "You entered an empty string.\n"
					  << "Enter the word or phrase you want to translate." << std::endl;
			continue;
		}

		if (inputString != DIALOG_EXIT_KEY)
		{
			FindWordInDictionary(inputString, Dictionary, outputString);
			if (!outputString.empty())
			{
				OutputStringToStream(outputString, std::cout);
				continue;
			}
			else
			{
				HandleAddingWordToDictionary(inputString, Dictionary);
				continue;
			}
		}
	} while (inputString != DIALOG_EXIT_KEY);
}

void OutputDictionaryToStream(const std::multimap<std::string, std::string>& Dictionary, std::ofstream& out)
{
	if (!Dictionary.empty())
	{
		for (auto it = Dictionary.begin(); it != Dictionary.end(); ++it)
		{
			out << "{" << it->first << "}{" << it->second << "}" << std::endl;
		}
	}
}

void HandleDictionarySaving(const std::multimap<std::string, std::string>& Dictionary, const std::string& fileName)
{
	std::cout << "The dictionary has been modified. Enter Y or y to save before exiting." << std::endl;
	std::string savingKey;
	InputStreamToString(std::cin, savingKey);
	if (savingKey == "Y" || savingKey == "y")
	{
		std::ofstream output(fileName);
		if (!output.is_open())
		{
			std::cout << "Failed to open '" << fileName << "' for writing." << std::endl;
			output.close();
			return;
		}
		OutputDictionaryToStream(Dictionary, output);
		if (!output.flush())
		{
			std::cout << "An error occurred while saving to file" << std::endl;
		}
		else
		{
			std::cout << "Changes saved." << std::endl;
		}
		output.close();
	}
	else
	{
		std::cout << "Changes not saved." << std::endl;
	}
}

void PrintDictionaryInformation()
{
	std::cout << "Hello !This is an English - Russian and Russian - English dictionary.\n"
			  << "Enter the word you want to translate.\n"
			  << "If you want to exit, enter << ... >> (a line consisting of three dots)" << std::endl;
}

void PrintExitInformation()
{
	std::cout << "The program closes, all the best!" << std::endl;
}

void DictionaryCLI(const std::string& fileName)
{
	std::multimap<std::string, std::string> Dictionary;
	DictionaryInitialization(fileName, Dictionary);
	size_t dictionaryCounter = Dictionary.size();
	PrintDictionaryInformation();
	ProcessDictionary(Dictionary);
	if (dictionaryCounter != Dictionary.size())
	{
		HandleDictionarySaving(Dictionary, fileName);
	}
	PrintExitInformation();
}
