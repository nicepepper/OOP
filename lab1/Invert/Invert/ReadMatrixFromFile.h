#pragma once
#include "Matrix3x3.h"
#include <fstream>
#include <optional>
#include <sstream>
#include <string>

std::optional<Matrix> ReadMatrixFromFile(const std::string filaName);
