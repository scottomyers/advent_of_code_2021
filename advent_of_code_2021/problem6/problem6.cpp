#include <iomanip>
#include <iostream>
#include <vector>

std::vector<int> example_input{ 3,4,3,1,2 };
std::vector<int> my_input{ 3,4,3,1,2,1,5,1,1,1,1,4,1,2,1,1,2,1,1,1,3,4,4,4,1,3,2,1,3,4,1,1,3,4,2,5,5,3,3,3,5,1,4,1,2,3,1,1,1,4,1,4,1,5,3,3,1,4,1,5,1,2,2,1,1,5,5,2,5,1,1,1,1,3,1,4,1,1,1,4,1,1,1,5,2,3,5,3,4,1,1,1,1,1,2,2,1,1,1,1,1,1,5,5,1,3,3,1,2,1,3,1,5,1,1,4,1,1,2,4,1,5,1,1,3,3,3,4,2,4,1,1,5,1,1,1,1,4,4,1,1,1,3,1,1,2,1,3,1,1,1,1,5,3,3,2,2,1,4,3,3,2,1,3,3,1,2,5,1,3,5,2,2,1,1,1,1,5,1,2,1,1,3,5,4,2,3,1,1,1,4,1,3,2,1,5,4,5,1,4,5,1,3,3,5,1,2,1,1,3,3,1,5,3,1,1,1,3,2,5,5,1,1,4,2,1,2,1,1,5,5,1,4,1,1,3,1,5,2,5,3,1,5,2,2,1,1,5,1,5,1,2,1,3,1,1,1,2,3,2,1,4,1,1,1,1,5,4,1,4,5,1,4,3,4,1,1,1,1,2,5,4,1,1,3,1,2,1,1,2,1,1,1,2,1,1,1,1,1,4 };

namespace fish {
	int_least64_t simulation(std::vector<int> starting_fish, int days)
	{
		std::vector<int_least64_t> fishes(9, 0);
		for (auto fish : starting_fish)
			++fishes[fish];

		for (int i = 0; i < days; ++i) {
			int_least64_t new_fish{ fishes[0] };
			for (int j = 0; j < fishes.size() - 1; ++j) {
				fishes[j] = fishes[j + 1];
			}
			fishes[6] += new_fish;
			fishes[8] = new_fish;
		}

		int_least64_t sum{};
		for (int i = 0; i < fishes.size(); ++i)
			sum += fishes[i];
		return sum;
	}
}

int main()
{
	std::cout << fish::simulation(my_input, 80) << '\n';
	std::cout << fish::simulation(my_input, 256) << '\n';
	return 0;
}