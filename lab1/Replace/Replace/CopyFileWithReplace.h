#pragma once
#include <fstream>
#include <string>

void CopyFileWithReplace(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString);
