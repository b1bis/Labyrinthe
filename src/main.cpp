#include "MazeGenerator.hpp"
#include "PPMWriter.hpp"

#include <ctime>
#include <fstream>

int main(int argc, char** argv)
{
	MazeGenerator generator;
	Maze maze = generator.Generate(50, 50, static_cast<unsigned>(time(nullptr)));

	PPMWriter writer(Color(255, 255, 255), Color(0, 0, 255), Color(255, 0, 0));
	std::ofstream file("maze.ppm");
	writer.Write(file, maze);

	std::cout << maze << std::endl;
	return 0;
}