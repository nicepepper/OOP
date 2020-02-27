// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MatrixFunctions.h"
#include "ReadMatrixFromFile.h"
#include <iostream>
#include <optional>
#include <string>

std::optional<Matrix> TryInvertMatrix(Matrix& matrix)
{
	float det = GetMatrixDeterminant3x3(matrix);
	if (det == 0)
	{
		return std::nullopt;
	}
	TransposeMatrix3x3(matrix);
	Matrix complements = GetComplementMatrix3x3(matrix);
	MultipleMatrixByNumber(complements, 1 / det);
	return complements;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "No input file specified!\n"
				  << "Usage : Invert.exe <matrix file1>" << std::endl;
		return 1;
	}
	if (auto matrix = ReadMatrixFromFile(argv[1]))
	{
		if (matrix = TryInvertMatrix(*matrix))
		{
			PrintMatrix(*matrix);
			return 0;
		}
		std::cout << "Matrix determinant is equal to zero" << std::endl;
	}
	else
	{
		std::cout << "Errors have occurred while reading your matrix from file" << std::endl;
	}
	return 1;
}
