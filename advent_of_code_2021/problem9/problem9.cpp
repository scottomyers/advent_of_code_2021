#include "heightmap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void part1(p9::HeightMap& t_hmap)
{
	int risk{ 0 };
	for (auto& lp : t_hmap.lowpoints()) {
		risk += t_hmap.at(lp) + 1;
	}
	std::cout << "Part 1: " << risk << std::endl;
}

void part2(p9::HeightMap& t_hmap)
{
	auto basins{ t_hmap.basins() };
	std::vector<int> sizes{};
	for (auto& b : basins) {
		sizes.push_back(static_cast<int>(b.size()));
	}

	std::sort(sizes.begin(), sizes.end(), std::greater<int>());
	std::cout << "Part 2: " << sizes[0] * sizes[1] * sizes[2] << std::endl;
}

int main()
{
	std::vector<std::vector<int>> example_data{
		{ 2,1,9,9,9,4,3,2,1,0 },
		{ 3,9,8,7,8,9,4,9,2,1 },
		{ 9,8,5,6,7,8,9,8,9,2 },
		{ 8,7,6,7,8,9,6,7,8,9 },
		{ 9,8,9,9,9,6,5,6,7,8 }
	};

	p9::HeightMap example{ example_data };
	p9::HeightMap my_input{ "input.txt" };

	part1(example);		// 15
	part1(my_input);	// 512

	part2(example);		// 1134
	part2(my_input);	// 1600104

	return 0;
}
