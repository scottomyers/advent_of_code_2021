#include "octopus.h"
#include <iostream>
#include <vector>

p11::OctopusGrid::OctopusGrid(std::vector<int>& t_grid)
	:m_grid{ t_grid }
{
}

int p11::OctopusGrid::at(const std::pair<int, int>& t_pos) const
{
	if (t_pos.first >= m_grid_height || t_pos.first < 0 || t_pos.second < 0 || t_pos.second >= m_grid_width) {
		return -1;
	}
	return m_grid.at(t_pos.first * m_grid_height + t_pos.second);
}

int p11::OctopusGrid::current_flashes() const
{
	int flashes{ 0 };
	for (const auto& o : m_grid) {
		if (o == 0) {
			++flashes;
		}
	}
	return flashes;
}

bool p11::OctopusGrid::flashed(const std::pair<int, int> t_pos) const
{
	return m_flashed[t_pos.first * m_grid_height + t_pos.second];
}

int p11::OctopusGrid::total_flashes() const
{
	return m_total_flashes;
}

std::vector<std::pair<int, int>> p11::OctopusGrid::neighbors(const std::pair<int, int> t_pos) const
{
	std::vector<std::pair<int, int>> n{};

	for (int row = t_pos.first - 1; row <= t_pos.first + 1; ++row) {
		for (int col = t_pos.second - 1; col <= t_pos.second + 1; ++col) {
			std::pair<int, int> pos{ row, col };
			if (at(pos) >= 0 && at(pos) <= 9) {
				n.push_back(pos);
			}
		}
	}

	return n;
}

void p11::OctopusGrid::print() const
{
	for (int i = 0; i < m_grid_height; ++i) {
		for (int j = 0; j < m_grid_width; ++j) {
			OctopusGrid::print(std::pair<int, int>{i, j});
		}
		std::cout << '\n';
	}
}

void p11::OctopusGrid::print(const std::pair<int, int>& t_pos) const
{
	int val{ at(t_pos) };
	if (val == 0) {
		std::cout << "*";
	}
	else {
		std::cout << val;
	}
}

void p11::OctopusGrid::step()
{
	for (int row = 0; row < m_grid_height; ++row) {
		for (int col = 0; col < m_grid_width; ++col) {
			step(std::pair<int, int>{row, col});
		}
	}
	for (int i = 0; i < (m_grid_height * m_grid_width); ++i) {
		m_flashed[i] = false;
	}
}

void p11::OctopusGrid::step(const std::pair<int, int>& t_pos)
{
	if (flashed(t_pos)) { return; }

	int new_val{ (at(t_pos) + 1) % 10 };
	m_grid[t_pos.first * m_grid_height + t_pos.second] = new_val;

	if (new_val == 0) {
		m_flashed[t_pos.first * m_grid_height + t_pos.second] = true;
		++m_total_flashes;
		for (auto& n : neighbors(t_pos)) {
			if (!flashed(n)) {
				step(n);
			}
		}
	}
}
