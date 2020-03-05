#pragma once
#include "Matrix3x3.h"
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>

float GetMatrixDeterminant3x3(const Matrix& matrix);
void MultiplyMatrixByNumber(Matrix& matrix, float number);
void TransposeMatrix3x3(Matrix& matrix);
Matrix GetComplementMatrix3x3(const Matrix& matrix);
void PrintMatrix(const Matrix& matrix);
