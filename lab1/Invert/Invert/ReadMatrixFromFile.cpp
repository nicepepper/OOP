#include "ReadMatrixFromFile.h"

// надо ли проверять корректность данных в файле ?
bool InitializeMatrixRow(Matrix& matrix, int rowNumber, const std::string& str)
{
	std::istringstream strStream(str);
	strStream.exceptions(std::ios::failbit);
	for (size_t i = 0; i < SQUARE_MATRIX_SIZE; i++)
	{
		float number(0);
		try
		{
			strStream >> number;
		}
		catch (const std::exception&)
		{
			return false;
		}
		matrix[rowNumber][i] = number;
	}
	return true;
}

std::optional<Matrix> ReadMatrixFromFile(const std::string fileName)
{
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		return std::nullopt;
	}

	Matrix matrix;
	std::string str;
	int rowCounter = 0;

	while (std::getline(input, str) && (rowCounter < SQUARE_MATRIX_SIZE))
	{
		if (!InitializeMatrixRow(matrix, rowCounter, str))
		{
			return std::nullopt;
		}
		if (rowCounter == SQUARE_MATRIX_SIZE - 1)
		{
			return matrix;
		}
		rowCounter++;
	}
	return std::nullopt;
}
