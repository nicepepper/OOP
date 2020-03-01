#pragma once
#include <fstream>
#include <string>
#include <iostream>

void CopyFileWithReplace(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString);

bool CopyWithReplace(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchString, const std::string& replaceString);