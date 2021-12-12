#include "heightmap.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

p9::HeightMap::HeightMap(const std::string& t_filename)
	:m_input{}, m_rows{ 0 }, m_cols{ 0 }
{
	std::ifstream is{ t_filename };
	std::string line{};
	char c;
	while (std::getline(is, line)) {
		std::istringstream iss{ line };
		std::vector<int> row{};
		while (iss >> c) {
			if (c != '\n') {
				row.push_back(c - '0');
			}
		}
		m_input.push_back(row);
	}
	m_rows = static_cast<int>(m_input.size());
	m_cols = static_cast<int>(m_input[0].size());
}

p9::HeightMap::HeightMap(std::vector<std::vector<int>>& t_input)
	:m_input{ t_input },
	m_rows{ static_cast<int>(t_input.size()) },
	m_cols{ static_cast<int>(t_input[0].size()) }
{
}

std::vector<std::pair<int, int>> p9::HeightMap::lowpoints() const
{
	std::vector<std::pair<int, int>> lps{};
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j) {
			std::pair<int, int> p{ i, j };
			if (is_lowpoint(p)) {
				lps.push_back(p);
			}
		}
	}
	return lps;
}

std::vector<std::pair<int, int>> p9::HeightMap::neighbors(const std::pair<int, int> t_point) const
{
	std::vector<std::pair<int, int>> nbors{};
	int row{ t_point.first };
	int col{ t_point.second };

	// up
	if (row > 0) nbors.push_back(std::pair<int, int>{row - 1, col});
	// down
	if (row < m_rows - 1) nbors.push_back(std::pair<int, int>{row + 1, col});
	// left
	if (col > 0) nbors.push_back(std::pair<int, int>{row, col - 1});
	// right
	if (col < m_cols - 1) nbors.push_back(std::pair<int, int>{row, col + 1});

	return nbors;
}

int p9::HeightMap::at(const std::pair<int, int>& t_point) const
{
	if (0 <= t_point.first && t_point.first <= m_rows - 1 && 0 <= t_point.second && t_point.second <= m_cols - 1)
		return m_input[t_point.first][t_point.second];
	return -1;
}

// base case: current node is 9 or has been visited -> return empty
// single step: add current node to basins and mark it visited
// recursive call: call grow_basin on each neighbor and add the results to the basins list
std::vector<std::pair<int, int>> p9::HeightMap::grow_basin(std::pair<int, int> node, std::vector<std::vector<bool>>& visited) const
{
	std::vector<std::pair<int, int>> basins{};

	if (at(node) == 9 || visited[node.first][node.second]) {
		return basins;
	}

	basins.push_back(node);
	visited[node.first][node.second] = true;
	for (auto& n : neighbors(node)) {
		for (auto& b : grow_basin(n, visited)) {
			basins.push_back(b);
		}
	}
	return basins;
}


std::vector<std::pair<int, int>> p9::HeightMap::grow_basin(const std::pair<int, int> t_root) const
{
	auto visited = std::vector<std::vector<bool>>(m_rows, std::vector<bool>(m_cols));
	return grow_basin(t_root, visited);
}

std::vector<std::vector<std::pair<int, int>>> p9::HeightMap::basins() const
{
	std::vector<std::vector<std::pair<int, int>>> basins{};
	for (auto& lp : lowpoints()) {
		basins.push_back(grow_basin(lp));
	}
	return basins;
}


bool p9::HeightMap::is_lowpoint(const std::pair<int, int>& t_point) const
{
	for (auto& n : neighbors(t_point)) {
		if (at(n) <= at(t_point)) {
			return false;
		}
	}
	return true;
}

void p9::print_point(const std::pair<int, int>& t_point)
{
	std::cout << '(' << t_point.first << ',' << t_point.second << ')';
}
