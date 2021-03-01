#include "PPMWriter.hpp"

PPMWriter::PPMWriter(Color emptyColor, Color wallColor, Color startColor)
	: m_emptyColor(emptyColor), m_wallColor(wallColor), m_startColor(startColor)
{
}

std::ostream& PPMWriter::Write(std::ostream& out, const Maze& maze) const
{
	out << "P3" << std::endl 
		<< maze.GetWidth() << " " << maze.GetHeight() << std::endl
		<< "255" << std::endl;
	for (std::size_t y = 0; y < maze.GetHeight(); ++y)
	{
		for (std::size_t x = 0; x < maze.GetWidth(); ++x)
		{
			switch (maze.GetState(x, y))
			{
			case Maze::Empty:
				out << m_emptyColor;
				break;
			case Maze::Wall:
				out << m_wallColor;
				break;
			case Maze::Start:
				out << m_startColor;
				break;
			default:
				out << m_emptyColor;
				break;
			}
			out << std::endl;
		}
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const Color& color)
{
	out << static_cast<int>(color.r) << " "
		<< static_cast<int>(color.g) << " "
		<< static_cast<int>(color.b);
	return out;
}
