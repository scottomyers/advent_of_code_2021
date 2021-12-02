#pragma once

struct Position
{
	int horizontal;
	int depth;
};

class Submarine
{
public:
	Submarine();
	~Submarine();

	int aim();
	Position position();
	void move(int t_units);
	void set_aim(int t_aim);

private:
	int m_aim;
	Position m_pos;
};

Submarine::Submarine()
	:m_aim{ 0 }, m_pos{ 0,0 }
{
}

Submarine::~Submarine()
{
}

Position Submarine::position()
{
	return m_pos;
}

int Submarine::aim()
{
	return m_aim;
}

void Submarine::move(int t_units)
{
	m_pos.horizontal += t_units;
	m_pos.depth += m_aim * t_units;
}

void Submarine::set_aim(int t_aim)
{
	m_aim = t_aim;
}