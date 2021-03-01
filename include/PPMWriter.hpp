#pragma once

#include <cstdint>
#include <iostream>
#include "Maze.hpp"

struct Color
{
	Color(std::uint8_t r_, std::uint8_t g_, std::uint8_t b_) :
		r(r_), g(g_), b(b_) {}
	std::uint8_t r, g, b;
};

std::ostream& operator<<(std::ostream& out, const Color& color);

class PPMWriter
{
public:
	PPMWriter(Color emptyColor, Color wallColor, Color startColor);
	std::ostream& Write(std::ostream& out, const Maze& maze) const;
private:
	Color m_emptyColor, m_wallColor, m_startColor;
};