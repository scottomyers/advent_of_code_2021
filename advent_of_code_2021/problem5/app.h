#pragma once
#include <string>
#include <vector>

struct Point
{
	int x;
	int y;
};
std::ostream& operator<<(std::ostream& os, const Point& p);

struct Line
{
	Point start;
	Point end;
};
std::ostream& operator<<(std::ostream& os, const Line& l);

struct Grid
{
	std::vector<std::vector<int>> m_grid;
};
std::ostream& operator<<(std::ostream& os, const Grid& g);

class App
{
public:
	Grid build_empty_grid(int x, int y) const;
	Grid build_grid(const std::vector<Line>& lines) const;
	int count_overlaps() const;
	std::vector<Line> parse_lines(const std::string& filename);
	std::vector<Point> points(const Line& l) const;
	void run();
	void set_grid(const Grid& t_grid);

private:
	Grid m_grid;
	int m_max_x;
	int m_max_y;
};

