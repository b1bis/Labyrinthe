#include "Maze.hpp"

Maze::Maze(std::size_t width, std::size_t height)
	: m_states(width, std::vector<State>(height, State::Empty))
{
}

std::ostream& operator<<(std::ostream& out, const Maze& maze)
{
	for (std::size_t y = 0; y < maze.GetHeight(); ++y)
	{
		for (std::size_t x = 0; x < maze.GetWidth(); ++x)
		{
			switch (maze.GetState(x, y))
			{
			case Maze::Empty:
				out << " ";
				break;
			case Maze::Wall:
				out << "#";
				break;
			case Maze::Start:
				out << ".";
				break;
			default:
				out << " ";
				break;
			}
		}
		out << "\n";
	}
	return out;
}
