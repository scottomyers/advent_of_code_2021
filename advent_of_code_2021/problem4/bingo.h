#pragma once
#include <string>
#include <vector>

class BingoBoard
{
public:
	BingoBoard();
	BingoBoard(const std::vector<std::string>& t_board);
	~BingoBoard();

	bool mark(int t_number);
	int sum_unmarked_numbers() const;
	bool winner() const;
	std::vector<int> winning_numbers() const;

	friend std::ostream& operator<<(std::ostream& os, const BingoBoard& t_board);

private:
	std::vector<std::vector<int>> m_board;
	std::vector<std::vector<bool>> m_marked;
};

