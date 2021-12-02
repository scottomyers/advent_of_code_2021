#include "submarine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int solve_part1(std::istream& is)
{
	Position p{ 0,0 };
	std::string direction{};
	int magnitude{};
	while (is >> direction >> magnitude) {
		if (direction == "down") {
			p.depth += magnitude;
		}
		else if (direction == "up") {
			p.depth -= magnitude;
		}
		else if (direction == "forward") {
			p.horizontal += magnitude;
		}
	}
	return p.horizontal * p.depth;
}

int solve_part2(std::istream& is)
{
	Submarine s{};
	std::string direction{};
	int magnitude{};
	while (is >> direction >> magnitude) {
		if (direction == "forward") {
			s.move(magnitude);
		}
		else if (direction == "down") {
			s.set_aim(s.aim() + magnitude);
		}
		else if (direction == "up") {
			s.set_aim(s.aim() - magnitude);
		}
	}
	return s.position().depth * s.position().horizontal;
}

void rewind(std::istream& is)
{
	is.clear();
	is.seekg(0, std::ios::beg);
}

int main()
{
	std::ifstream example_infile{ "example-input.txt" };
	std::cout << "Example Part 1: " << solve_part1(example_infile) << '\n';

	std::ifstream infile{ "input.txt" };
	std::cout << "Part 1: " << solve_part1(infile) << std::endl;

	rewind(example_infile);
	std::cout << "Example Part 2: " << solve_part2(example_infile) << '\n';

	rewind(infile);
	std::cout << "Part 2: " << solve_part2(infile) << std::endl;
	return 0;
}