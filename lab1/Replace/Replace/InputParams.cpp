#include "InputParams.h"

const int PARAMS_QUANTITY = 5;
const int INPUT_FILE_INDEX = 1;
const int OUTPUT_FILE_INDEX = 2;
const int SEARCH_STRING_INDEX = 3;
const int REPLACE_STRING_INDEX = 4;

std::string GetFileExtension(const std::string& fileName)
{
	auto lastDot = fileName.find_last_of(".");

	if (lastDot != std::string::npos)
	{
		return fileName.substr(lastDot + 1);
	}

	return std::string();
}

bool ValidateParams(int size, char* arguments[])
{
	bool isValid = true;

	isValid = isValid && (size == PARAMS_QUANTITY);
	//isValid = isValid && //как проверить существует ли файл
	isValid = isValid && (GetFileExtension(arguments[INPUT_FILE_INDEX]) == GetFileExtension(arguments[OUTPUT_FILE_INDEX]));
	isValid = isValid && (std::strlen(arguments[SEARCH_STRING_INDEX]) && std::strlen(arguments[REPLACE_STRING_INDEX]));

	return isValid;
}

AppParams CreateAppParams(char* arguments[])
{
	AppParams params;
	params.inputFileName = arguments[INPUT_FILE_INDEX];
	params.outputFileName = arguments[OUTPUT_FILE_INDEX];
	params.searchString = arguments[SEARCH_STRING_INDEX];
	params.replaceString = arguments[REPLACE_STRING_INDEX];

	return params;
}

std::optional<AppParams> ParseCommandLine(int size, char* arguments[])
{
	if (ValidateParams(size, arguments))
	{
		return CreateAppParams(arguments);
	}
	else
	{
		return std::nullopt;
	}
}
