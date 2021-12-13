#pragma once
#include <utility>
#include <vector>

namespace p11 {
	class OctopusGrid {
	public:
		OctopusGrid(std::vector<int>& t_grid);

		int at(const std::pair<int, int>& pos) const;
		int current_flashes() const;
		bool flashed(const std::pair<int, int> pos) const;
		std::vector<std::pair<int, int>> neighbors(const std::pair<int, int> pos) const;
		void print() const;
		void print(const std::pair<int, int>& pos) const;
		void step();
		int total_flashes() const;

	private:
		std::vector<int> m_grid;
		int m_grid_height{ 10 };
		int m_grid_width{ 10 };
		std::vector<bool> m_flashed{ std::vector<bool>(m_grid_height * m_grid_width, false) };
		int m_total_flashes{ 0 };

		void step(const std::pair<int, int>& pos);
	};
}
