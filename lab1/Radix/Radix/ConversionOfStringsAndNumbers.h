#pragma once
#include "inputValidator.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <vector>

TypeInteger StringToInt(const std::string& value, const TypeInteger& radix, bool& wasError);

std::string IntToString(TypeInteger number, const TypeInteger& radix, bool& wasError);
