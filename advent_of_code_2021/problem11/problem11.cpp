#include "octopus.h"
#include <iostream>
#include <Windows.h>

void cls(HANDLE hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

std::vector<int> example_data{
	5,4,8,3,1,4,3,2,2,3,
	2,7,4,5,8,5,4,7,1,1,
	5,2,6,4,5,5,6,1,7,3,
	6,1,4,1,3,3,6,1,4,6,
	6,3,5,7,3,8,5,4,7,8,
	4,1,6,7,5,2,4,6,4,5,
	2,1,7,6,8,4,1,7,2,1,
	6,8,8,2,8,8,1,1,3,4,
	4,8,4,6,8,4,8,5,5,4,
	5,2,8,3,7,5,1,5,2,6,
};

std::vector<int> my_data{
	5,2,5,1,5,7,8,1,8,1,
	6,1,5,8,4,5,2,3,1,3,
	1,8,1,8,5,7,8,5,7,1,
	3,8,4,4,6,1,5,1,4,3,
	6,8,5,7,2,5,1,2,4,4,
	2,3,7,5,8,1,7,6,1,3,
	8,8,8,3,5,1,4,4,3,5,
	2,3,2,1,2,6,5,7,3,5,
	2,8,5,7,2,7,5,1,8,2,
	4,8,2,1,1,5,6,6,4,4,
};

void part1()
{
	std::cout << "-------- Part 1 --------\n";
	p11::OctopusGrid og_example{ example_data };
	for (int i = 0; i < 100; ++i) {
		og_example.step();
	}
	og_example.print();
	std::cout << "Flashes: " << og_example.total_flashes() << std::endl;

	std::cout << '\n';

	p11::OctopusGrid og{ my_data };
	for (int i = 0; i < 100; ++i) {
		og.step();
	}
	og.print();
	std::cout << "Flashes: " << og.total_flashes() << std::endl;
}

void part2()
{
	std::cout << "-------- Part 2 --------\n";
	p11::OctopusGrid og_example{ example_data };
	int steps{ 0 };
	while (true) {
		if (og_example.current_flashes() == 100) {
			break;
		}
		og_example.step();
		++steps;
	}
	std::cout << "Flashes: " << steps << '\n';

	p11::OctopusGrid og{ my_data };
	steps = 0;
	while (true) {
		if (og.current_flashes() == 100) {
			break;
		}
		og.step();
		++steps;
	}
	std::cout << "Flashes: " << steps << '\n';
}

int main()
{
	part1(); // 1637
	part2(); // 242

	Sleep(3000);

	// visualization -- Windows only 
	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	cls(hStdout);

	p11::OctopusGrid og{ my_data };
	int cycles{ 0 };
	while (true) {
		og.print();
		std::cout << "Flashes: " << og.current_flashes() << '\n';
		std::cout << "Total flashes: " << og.total_flashes() << '\n';
		std::cout << "Total cycles: " << cycles << std::endl;
		og.step();
		++cycles;
		Sleep(1000);
		cls(hStdout);
	}
	return 0;
}
