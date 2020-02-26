#include "MatrixFunctions.h"

float GetComplementOfMatrix3x3(const Matrix& matrix, int y, int x)
{
	std::array<float, 4> matrixElement = {};
	int desiredItem = 0;
	for (int i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			if ((i != y) && (j != x))
			{
				matrixElement[desiredItem++] = matrix[i][j];
			}
		}
	}
	return ((matrixElement[0] * matrixElement[3]) - (matrixElement[1] * matrixElement[2]));
}

float GetMatrixDeterminant3x3(const Matrix& m)
{
	return (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1])
		- (m[0][2] * m[1][1] * m[2][0]) - (m[0][0] * m[1][2] * m[2][1]) - (m[0][1] * m[1][0] * m[2][2]);
}

void MultipleMatrixByNumber(Matrix& matrix, float number)
{
	for (size_t i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			matrix[i][j] = matrix[i][j] * number;
		}
	}
}
	

void TransposeMatrix3x3(Matrix& matrix)
{
	for (size_t i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}
}

Matrix GetComplementMatrix3x3(const Matrix& matrix)
{
	Matrix resultingMatrix;
	int sign = 1;
	for (size_t i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			resultingMatrix[i][j] = float(sign) * GetComplementOfMatrix3x3(matrix, i, j);
			sign *= -1;
		}
		return resultingMatrix;
	}
}

void PrintMatrix(const Matrix& matrix)
{
	for (size_t i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < SQUARE_MATRIX_SIZE; j++)
		{
			std::cout << std::setprecision(3) << std::fixed << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
