#pragma once

#include <array>

const size_t LABYRINTH_SIZE = 100;

const char EMPTY_CAGE = ' ';
const char START_POINT_SYMBOL = 'A';
const char END_POINT_SYMBOL = 'B';
const char WAY_SYMBOL = '.';
const char WALL_SYMBOL = '#';

using Labyrinth = std::array<std::array<size_t, LABYRINTH_SIZE>, LABYRINTH_SIZE>;

struct LabyrinthInformation
{
	int startPointX;
	int startPointY;

	int endPointX;
	int endPointY;

	Labyrinth labyrinth;
};