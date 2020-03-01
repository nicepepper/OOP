#pragma once
#include "ConstantsAndSourceData.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <string>
#include <vector>

bool IsNumberInString(const std::string& str);

bool StringValueSuitableForRadix(const std::string& str, int& number);

bool IsStringCorrectForNumberSystem(const std::string& value, const int sourceNotation);
