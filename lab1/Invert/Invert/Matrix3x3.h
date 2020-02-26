#pragma once
#include <array>
constexpr size_t SQUARE_MATRIX_SIZE = 3;

//можно как псевдоним объ€вить ?
using Matrix = std::array<std::array<float, SQUARE_MATRIX_SIZE>, SQUARE_MATRIX_SIZE>;
