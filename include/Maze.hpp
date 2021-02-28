#pragma once

#include <vector>
#include <iostream>

class Maze
{
	friend std::ostream& operator<<(std::ostream& out, const Maze& maze);
public:

	enum State
	{
		Empty,
		Wall,
		Start
	};

	Maze(std::size_t width, std::size_t height);

	inline std::size_t GetWidth() const { return m_states.size(); }
	inline std::size_t GetHeight() const { return m_states[0].size(); }

	inline State GetState(std::size_t x, std::size_t y) const { return m_states[x][y]; }
	inline void SetState(std::size_t x, std::size_t y, State state) { m_states[x][y] = state; }
private:
	using states_t = std::vector<std::vector<State>>;
	states_t m_states;
};

std::ostream& operator<<(std::ostream& out, const Maze& maze);