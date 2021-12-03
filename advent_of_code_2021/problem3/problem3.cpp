#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int bitset_size{ 12 };

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

void solve_part1(std::istream& is)
{
	std::string line{};
	std::getline(is, line);
	std::vector<int> zeroes(line.length(), 0);
	std::vector<int> ones(line.length(), 0);
	
	while (std::getline(is, line)) {
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
	std::cout << "Answer: " << (gamma.to_ulong() * epsilon.to_ulong()) << std::endl;
}

int main()
{
	std::ifstream example{ "example-input.txt" };
	solve_part1(example);

	std::ifstream input{ "input.txt" };
	solve_part1(input);
	return 0;
}