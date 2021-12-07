#include "app.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Grid App::build_empty_grid(int x, int y) const
{
	Grid g{};
	for (int i = 0; i < x; ++i) {
		g.grid.push_back(std::vector<int>(y, 0));
	}
	return g;
}

Grid App::build_grid(const std::vector<Line>& lines) const
{
	Grid g{ build_empty_grid(m_max_x + 1, m_max_y + 1) };

	for (auto& line : lines) {
		for (auto& p : points(line)) {
			++g.grid[p.x][p.y];
		}
	}

	return g;
}

int App::count_overlaps() const
{
	int count{};
	for (auto& row : m_grid.grid) {
		for (auto& cell : row) {
			if (cell > 1)
				++count;
		}
	}
	return count;
}

std::vector<Line> App::parse_lines(const std::string& filename)
{
	std::vector<Line> lines{};
	std::ifstream is{ filename };
	std::string line{};
	std::vector<char> replace_with_space{ ',', '-', '>' };
	while (std::getline(is, line)) {
		for (auto c : replace_with_space) {
			std::replace(line.begin(), line.end(), c, ' ');
		}

		std::istringstream iss{ line };
		int x1;
		int y1;
		int x2;
		int y2;
		iss >> x1 >> y1 >> x2 >> y2;

		int t_max_x{ x1 > x2 ? x1 : x2 };
		int t_max_y{ y1 > y2 ? y1 : y2 };
		if (t_max_x > m_max_x)
			m_max_x = t_max_x;
		if (t_max_y > m_max_y)
			m_max_y = t_max_y;
		lines.push_back(Line{ Point{x1, y1}, Point{x2, y2} });
	}
	return lines;
}

std::vector<Point> App::points(const Line& l) const
{
	std::vector<Point> points{};
	int start{};
	int end{};

	// horizontal
	if (l.end.y == l.start.y) {
		start = std::min(l.start.x, l.end.x);
		end = std::max(l.start.x, l.end.x);
		for (int i = start; i <= end; ++i) {
			points.push_back(Point{ i, l.start.y });
		}
	}
	// vertical
	else if (l.end.x == l.start.x) {
		start = std::min(l.start.y, l.end.y);
		end = std::max(l.start.y, l.end.y);
		for (int i = start; i <= end; ++i) {
			points.push_back(Point{ l.start.x, i });
		}
	}
	// diagonal
	else {
		int slope{ (l.end.y - l.start.y) / (l.end.x - l.start.x) };

		start = std::min(l.start.x, l.end.x);
		end = std::max(l.start.x, l.end.x);

		int starty{ start == l.start.x ? l.start.y : l.end.y };

		for (int i = 0; i <= (end - start); ++i) {
			points.push_back(Point{ start + i, starty + (i * slope) });
		}
	}
	return points;
}

void App::run()
{
	std::vector<Line> lines = parse_lines("input.txt");
	set_grid(build_grid(lines));
	std::cout << count_overlaps();
	Line l{ Point{1, 1}, Point{3, 3} };
	for (auto& p : points(l))
		std::cout << p << ' ';
}

void App::set_grid(const Grid& t_grid) { m_grid = t_grid; }

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << '(' << p.x << ',' << p.y << ')';
	return os;
}

std::ostream& operator<<(std::ostream& os, const Line& l)
{
	os << l.start << " -> " << l.end;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Grid& g)
{
	for (auto& l : g.grid) {
		for (auto& i : l) {
			os << std::setw(3) << i << ' ';
		}
		os << '\n';
	}
	return os;
}
