#include "InitializeLabyrinth.h"
#include <fstream>
#include <string>


struct InitializationData
{
	int lineNumber = 0;
	std::string line;
	bool foundStartPoint = false;
	bool foundEndPoint = false;
};



std::optional<LabyrinthInformation> InitializeLabyrinth(const std::string fileName)
{
	std::ifstream input(fileName);
	if (input.is_open())
	{
		return std::nullopt;
	}
	
	InitializationData initData;
	LabyrinthInformation labyrintInfo;



	return std::nullopt;
}
