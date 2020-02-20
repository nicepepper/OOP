#pragma once
#include <fstream>
#include <string>

void ReplaceSubstringsInTextFile(std::istream& input, std::ofstream& output, const std::string& searchString, const std::string& replaceString);