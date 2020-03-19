#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <vector>

std::optional<std::vector<double>> ReadingFromStreamToVector(std::istream& cin, std::vector<double>& numbers);
void ProcessVector(std::vector<double>& numbers);
void PrintVectorOfNumbers(const std::vector<double>& numbers, std::ostream& cout);
