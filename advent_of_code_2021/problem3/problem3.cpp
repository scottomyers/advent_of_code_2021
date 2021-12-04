#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int bitset_size{ 12 };

std::vector<std::string> read_lines(const std::string filename)
{
	std::string line{};
	std::vector<std::string> lines{};
	std::ifstream infile{ filename };
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}
	return lines;
}

std::bitset<bitset_size> calculate_gamma(const std::vector<int>& zeroes, const std::vector<int>& ones)
{
	std::bitset<bitset_size> gamma{};
	for (int i{ 0 }; i < zeroes.size(); ++i) {
		if (zeroes[i] < ones[i]) {
			gamma.set(bitset_size - i - 1);
		}
		else {
			gamma.reset(bitset_size - i - 1);
		}
	}
	if (zeroes.size() < bitset_size) {
		gamma >>= (bitset_size - zeroes.size());
	}
	return gamma;
}

std::bitset<bitset_size> calculate_epsilon(std::bitset<bitset_size>& gamma, int mask_bits = bitset_size)
{
	std::bitset<bitset_size> epsilon{ ~gamma };
	std::bitset<bitset_size> mask{};
	for (int i{ 0 }; i < mask_bits; ++i) {
		mask.set(i);
	}
	return epsilon & mask;
}

void solve_part1(const std::vector<std::string>& lines)
{
	std::vector<int> zeroes(lines[0].length(), 0);
	std::vector<int> ones(lines[0].length(), 0);

	for (auto& line : lines) {
		for (auto i{ 0 }; i < line.length(); ++i) {
			auto c = line[i];
			if (c == '0') {
				zeroes[i] += 1;
			}
			else if (c == '1') {
				ones[i] += 1;
			}
		}
	}

	std::bitset<bitset_size> gamma{ calculate_gamma(zeroes, ones) };
	std::bitset<bitset_size> epsilon{ calculate_epsilon(gamma, static_cast<int>(zeroes.size())) };
	std::cout << "Part 1: " << (gamma.to_ulong() * epsilon.to_ulong()) << std::endl;
}

unsigned long long calculate_oxygen_rating(const std::vector<std::string>& lines, int position = 0)
{
	if (lines.size() == 1) {
		return std::bitset<12>{lines[0]}.to_ullong();
	}

	int zeroes{ 0 };
	int ones{ 0 };
	for (auto& line : lines) {
		if (line[position] == '1') ++ones;
		else if (line[position] == '0') ++zeroes;
	}

	char winner{ '0' };
	if (ones >= zeroes) winner = '1';

	std::vector<std::string> candidates{};
	for (auto line : lines) {
		if (line[position] == winner) candidates.push_back(line);
	}
	return calculate_oxygen_rating(candidates, ++position);
}

unsigned long long calculate_co2_rating(const std::vector<std::string>& lines, int position = 0)
{
	if (lines.size() == 1) {
		return std::bitset<12>{lines[0]}.to_ullong();
	}

	int zeroes{ 0 };
	int ones{ 0 };
	for (auto& line : lines) {
		if (line[position] == '1') ++ones;
		else if (line[position] == '0') ++zeroes;
	}

	char winner{ '0' };
	if (ones < zeroes) winner = '1';

	std::vector<std::string> candidates{};
	for (auto line : lines) {
		if (line[position] == winner) candidates.push_back(line);
	}
	return calculate_co2_rating(candidates, ++position);
}

void solve_part2(const std::vector<std::string>& lines)
{
	unsigned long long co2{ calculate_co2_rating(lines) };
	unsigned long long o2{ calculate_oxygen_rating(lines) };
	std::cout << "Part 2: " << (o2 * co2) << std::endl;
}

int main()
{
	std::vector<std::string> example_input{ read_lines("example-input.txt") };
	solve_part1(example_input);

	std::vector<std::string> input{ read_lines("input.txt") };
	solve_part1(input);

	solve_part2(example_input);
	solve_part2(input);
	return 0;
}