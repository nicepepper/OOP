#pragma once
#include "ConstantsAndSourceData.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <string>
#include <vector>

bool isNumberInString(const std::string& str);

bool isNumberInRange(const std::string& str, int& number);

bool is—orrectValue(const std::string value, const int sourceNotation, const std::vector<char>& alphabet);
