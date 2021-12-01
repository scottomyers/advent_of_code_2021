#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::string example_input{ R"(199
200
208
210
200
207
240
269
260
263)" };

std::vector<int> parse_numbers(std::istream& is)
{
	std::vector<int> numbers{};
	for (std::string line; std::getline(is, line);) {
		numbers.push_back(std::stoi(line));
	}
	return numbers;
}

int solve_part1(const std::vector<int>& t_nums)
{
	int result{};
	int prev{ (t_nums.size() > 0) ? t_nums[0] : 0 };
	for (auto& n : t_nums) {
		if (n > prev)
			++result;
		prev = n;
	}
	return result;
}

int solve_part2(const std::vector<int>& t_nums)
{
	int count{ 0 };
	for (auto i{ t_nums.begin() }; i != t_nums.end() - 3; ++i) {
		int current{ i[0] + i[1] + i[2] };
		int next{ i[1] + i[2] + i[3] };
		if (current < next) ++count;
	}
	return count;
}

int main()
{
	std::istringstream iss{ example_input };
	std::vector<int> example_nums{ parse_numbers(iss) };
	std::cout << "Part 1 Example: " << solve_part1(example_nums) << '\n';

	std::string filename{ "input.txt" };
	std::ifstream infile{ filename };
	std::vector<int> nums{ parse_numbers(infile) };
	std::cout << "Part 1: " << solve_part1(nums) << '\n';

	std::cout << "Part 2 Example: " << solve_part2(example_nums) << '\n';
	std::cout << "Part 2: " << solve_part2(nums) << std::endl;
	return 0;
}