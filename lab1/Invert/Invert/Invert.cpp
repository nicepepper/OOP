// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MatrixFunctions.h"
#include "ReadMatrixFromFile.h"
#include <iostream>
#include <optional>
#include <string>

/*
РАЗРАБОТКА ПСЕВДОКОДА
*/
/*
проверить входные данные
параметров мало, потому использую
чистый argv для входных параметров
но надо проверить уже правильность заданных данных для инициализации нашего массива
не буду использовать метод элементарных преоброзоаний, что тро трудно придумать с разбегу алгоритм
будем использовать метот, через алгебраические дополнения
optional<Matrix> TryInvertMatrix
найти определитель (det)
если det = 0 => то обратной матрицы нет для заданной матрицы return nullopt;
ИНАЧЕ
транспонировть заданную матрицу
найти союзную матрицу
найти обратную матрицу A(-1) = A(*)  *  1/det
все.
A - заданная матрица
A(-1) - обратная матрица
A(*) - союзная матрица 
A(T) - Транспанированная матрица
если det != 0 => то A(-1) существует
при выводе матрицы использовать форматированный вывод с помущу iomanip -- манипуляторы(форматированный ввод.вывод с++)
*/
/*
КОНЕЦ РАЗРАБОКИ ПСЕВДОКОДА
*/

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
