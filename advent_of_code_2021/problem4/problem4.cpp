#include "bingo.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parse_bingo_nums(const std::string& filename) {
	std::ifstream infile{ filename };
	std::string line{};
	
	std::getline(infile, line);
	std::replace(line.begin(), line.end(), ',', ' ');

	std::vector<int> nums{};
	int num{};
	std::istringstream iss{ line };
	while (iss >> std::ws >> num) {
		nums.push_back(num);
	}
	return nums;
}

std::vector<BingoBoard> parse_bingo_boards(const std::string& filename)
{
	std::vector<std::string> lines{};
	std::string line{};
	std::ifstream is{ filename };
	while (std::getline(is, line))
		lines.push_back(line);

	std::vector<BingoBoard> boards{};

	for (int i = 2; i < lines.size(); ++i) {
		if (lines[i] == "\n") {
			continue;
		}

		std::vector<std::string> chunk(lines.begin() + i, lines.begin() + i + 5);
		boards.push_back(BingoBoard{ chunk });
		i += 5;
	}

	return boards;
}

void solve_part1()
{
	//std::string filename{ "example-input.txt" };
	std::string filename{ "input.txt" };
	
	std::vector<int> bingo_nums{ parse_bingo_nums(filename) };
	std::vector<BingoBoard> boards{ parse_bingo_boards(filename) };
	std::shared_ptr<BingoBoard> winner;

	int last_num_called{};
	for (auto& num : bingo_nums) {
		last_num_called = num;
		std::cout << "Calling " << last_num_called << "...\n";
		for (auto& board : boards) {
			board.mark(num);
			if (board.winner()) {
				winner = std::make_shared<BingoBoard>(board);
				std::cout << "We have a winning board!\n\n";
				break;
			}
		}

		if (winner) break;
	}

	
	if (winner) {
		std::cout << "Winning board:\n" << *winner << '\n';
		std::cout << "Winning row: ";
		for (auto& num : winner->winning_numbers()) {
			std::cout << num << ' ';
		}
		std::cout << '\n';

		std::cout << "Unmarked numbers * last number called = " << (winner->sum_unmarked_numbers() * last_num_called) << '\n';
	}
	std::cout << std::endl;
}

void solve_part2()
{
	//std::string filename{ "example-input.txt" };
	std::string filename{ "input.txt" };

	std::vector<int> bingo_nums{ parse_bingo_nums(filename) };
	std::vector<BingoBoard> boards{ parse_bingo_boards(filename) };
	std::shared_ptr<BingoBoard> last_winner;
	std::vector<std::vector<int>> winning_numbers{};

	int last_num_called{};
	for (auto& num : bingo_nums) {
		last_num_called = num;
		std::cout << "Calling " << last_num_called << "...\n";
		for (auto& board : boards) {
			if (board.winner() && std::find(winning_numbers.begin(), winning_numbers.end(), board.winning_numbers()) != winning_numbers.end()) {
				continue;
			}

			board.mark(num);
			if (board.winner() && std::find(winning_numbers.begin(), winning_numbers.end(), board.winning_numbers()) == winning_numbers.end()) {
				last_winner = std::make_shared<BingoBoard>(board);
				winning_numbers.push_back(board.winning_numbers());
			}

			if (winning_numbers.size() == boards.size()) break;
		}
		if (winning_numbers.size() == boards.size()) break;
	}

	if (last_winner) {
		std::cout << "Last winner was:\n" << *last_winner << '\n';

		std::cout << "Number of winners: " << winning_numbers.size() << '\n';
		std::cout << "Number of boards: " << boards.size() << '\n';


		
		std::cout << "Unmarked numbers * last number called = " << (last_winner->sum_unmarked_numbers() * last_num_called) << '\n';
	}
	std::cout << std::endl;
}

int main()
{
	std::cout << "========== Part 1 ==========\n";
	solve_part1();
	
	std::cout << "\n========== Part 2 ==========\n";
	solve_part2();

	return 0;
}
