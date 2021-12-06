#include "bingo.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int board_size = 5;

BingoBoard::BingoBoard()
	:m_board{ std::vector<std::vector<int>> {} }, m_marked{ std::vector<std::vector<bool>> {} }
{
}

BingoBoard::BingoBoard(const std::vector<std::string>& t_board)
	: m_board{ std::vector<std::vector<int>> {} }, m_marked{ std::vector<std::vector<bool>> {} }
{
	int num{};
	for (int i = 0; i < board_size; ++i) {
		std::istringstream in{ t_board[i] };
		std::vector<int> nums{};
		while (in >> num) {
			nums.push_back(num);
		}
		m_board.push_back(nums);
		m_marked.push_back(std::vector<bool>{false, false, false, false, false});
	}
}

BingoBoard::~BingoBoard()
{
}

bool BingoBoard::mark(int t_number)
// assumes t_number appears on the board at most once
{
	for (int i = 0; i < board_size; ++i) {
		for (int j = 0; j < board_size; ++j) {
			if (m_board[i][j] == t_number) {
				m_marked[i][j] = true;
				return true;
			}
		}
	}
	return false;
}

int BingoBoard::sum_unmarked_numbers() const
{
	int sum{};
	for (int i = 0; i < board_size; ++i) {
		for (int j = 0; j < board_size; ++j) {
			if (not m_marked[i][j]) {
				sum += m_board[i][j];
			}
		}
	}
	return sum;
}

bool BingoBoard::winner() const
{
	for (int i = 0; i < board_size; i++) {
		// check row
		if (m_marked[i][0] && m_marked[i][1] && m_marked[i][2] && m_marked[i][3] && m_marked[i][4]) {
			return true;
		}
		// check column
		if (m_marked[0][i] && m_marked[1][i] && m_marked[2][i] && m_marked[3][i] && m_marked[4][i]) {
			return true;
		}
	}
	return false;
}

std::vector<int> BingoBoard::winning_numbers() const
{
	std::vector<int> winning_nums{};
	for (int i = 0; i < board_size; i++) {
		// check row
		if (m_marked[i][0] && m_marked[i][1] && m_marked[i][2] && m_marked[i][3] && m_marked[i][4]) {
			return std::vector<int>{m_board[i][0], m_board[i][1], m_board[i][2], m_board[i][3], m_board[i][4]};
		}
		// check column
		if (m_marked[0][i] && m_marked[1][i] && m_marked[2][i] && m_marked[3][i] && m_marked[4][i]) {
			return std::vector<int>{m_board[0][i], m_board[1][i], m_board[2][i], m_board[3][i], m_board[4][i]};
		}
	}
	return winning_nums;
}

std::ostream& operator<<(std::ostream& os, const BingoBoard& t_board)
{
	for (int i = 0; i < board_size; ++i) {
		for (auto& num : t_board.m_board[i]) {
			std::cout << std::setw(3) << num << ' ';
		}
		std::cout << '\n';
	}
	return os;
}
