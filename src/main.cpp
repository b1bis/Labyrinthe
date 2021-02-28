#include "MazeGenerator.hpp"
#include <iostream>


int main(int argc, char** argv)
{
	MazeGenerator generator;
	std::cout << generator.Generate(24, 10, 6) << std::endl;
	return 0;
}