#include "MatrixFunctions.h"

float GetComplementOfMatrix3x3(const Matrix& matrix, int y, int x)
{
	std::array<float, 4> matrixElements = { 0 };

	int itemIndex = 0;

	for (int i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			if ((i != y) && (j != x))
			{
				matrixElements[itemIndex++] = matrix[i][j];
			}
		}
	}
	return ((matrixElements[0] * matrixElements[3]) - (matrixElements[1] * matrixElements[2]));
}

float GetMatrixDeterminant3x3(const Matrix& m)
{
	return (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1])
		- (m[0][2] * m[1][1] * m[2][0]) - (m[0][0] * m[1][2] * m[2][1]) - (m[0][1] * m[1][0] * m[2][2]);
}

void TransposeMatrix3x3(Matrix& matrix)
{
	for (int i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (int j = i; j < SQUARE_MATRIX_SIZE; j++)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}
}

Matrix GetComplementMatrix3x3(const Matrix& matrix)
{
	Matrix complementMatrix3x3;
	float sign = 1;
	for (int i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			complementMatrix3x3[i][j] = sign * GetComplementOfMatrix3x3(matrix, i, j);
			sign = -sign;
		}
	}
	return complementMatrix3x3;
}

void MultiplyMatrixByNumber(Matrix& matrix, float number)
{
	for (auto& row : matrix)
	{
		for (auto& item : row)
		{
			item *= number;		
		}
	}
}

void PrintMatrix(const Matrix& matrix)
{
	for (auto& row : matrix)
	{
		for (auto& item : row)
		{
			std::cout << std::setprecision(3) << std::fixed << item << " ";
		}
		std::cout << std::endl;
	}
}