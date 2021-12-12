#pragma once

#include <string>
#include <utility>
#include <vector>

namespace p9 {
	class HeightMap {
	public:
		HeightMap(const std::string& filename);
		HeightMap(std::vector<std::vector<int>>& t_input);

		int at(const std::pair<int, int>& point) const;
		std::vector<std::vector<std::pair<int, int>>> basins() const;
		std::vector<std::pair<int, int>> grow_basin(const std::pair<int, int> root) const;
		bool is_lowpoint(const std::pair<int, int>& point) const;
		std::vector<std::pair<int, int>> lowpoints() const;
		std::vector<std::pair<int, int>> neighbors(const std::pair<int, int> point) const;

	private:
		std::vector<std::pair<int, int>> grow_basin(std::pair<int, int> node, std::vector<std::vector<bool>>& visited) const;
		int m_cols;
		int m_rows;
		std::vector<std::vector<int>> m_input;
	};

	void print_point(const std::pair<int, int>& point);
}
