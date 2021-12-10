#pragma once
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> example_data{
	{ 2,1,9,9,9,4,3,2,1,0 },
	{ 3,9,8,7,8,9,4,9,2,1 },
	{ 9,8,5,6,7,8,9,8,9,2 },
	{ 8,7,6,7,8,9,6,7,8,9 },
	{ 9,8,9,9,9,6,5,6,7,8 }
};



std::vector<int> find_neighbors(const std::vector<std::vector<int>>& data, int row, int col)
{
	std::vector<int> neighbors{};

	// left
	if (col > 0) {
		neighbors.push_back(data[row][col - 1]);
	}
	// down
	if (row < (data.size() - 1)) {
		neighbors.push_back(data[row + 1][col]);
	}
	// right 
	if (col < (data[0].size() - 1)) {
		neighbors.push_back(data[row][col + 1]);
	}
	// up
	if (row > 0) {
		neighbors.push_back(data[row - 1][col]);
	}

	return neighbors;
}

bool is_lowpoint(const std::vector<std::vector<int>>& data, int row, int col)
{
	for (auto& neighbor : find_neighbors(data, row, col)) {
		if (neighbor <= data[row][col]) {
			return false;
		}
	}
	return true;
}

std::vector<int> find_lowpoints(const std::vector<std::vector<int>>& data)
{
	std::vector<int> lowpoints{};
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			if (is_lowpoint(data, i, j)) {
				lowpoints.push_back(data[i][j]);
			}
		}
	}
	return lowpoints;
}

void part1(const std::vector<std::vector<int>>& data)
{
	int risk{ 0 };
	
	for (auto& lowpoint : find_lowpoints(data))
		risk += lowpoint + 1;

	std::cout << "Part 1: " << risk << '\n';
}