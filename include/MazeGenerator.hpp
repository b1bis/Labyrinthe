#pragma once

#include "Maze.hpp"
#include <random>

class MazeGenerator
{
public:
	MazeGenerator() = default;
	Maze Generate(std::size_t width, std::size_t height, unsigned seed);
private:
	Maze ToMaze(const std::vector<std::vector<int>>& durtyMaze);
	std::vector<std::vector<int>> GenerateGrid(std::size_t width, std::size_t height);
	bool IsComplete(const std::vector<std::vector<int>>& durtyMaze);
};