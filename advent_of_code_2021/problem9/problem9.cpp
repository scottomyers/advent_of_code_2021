#include "problem9.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<std::vector<int>> my_data{};
	std::ifstream iss{ "input.txt" };
	std::string line{};
	while (std::getline(iss, line)) {
		std::vector<int> nums{};
		for (auto& c : line) {
			if (c != '\n') {
				nums.push_back(c - '0');
			}
		}
		my_data.push_back(nums);
	}

	part1(my_data);

	return 0;
}
