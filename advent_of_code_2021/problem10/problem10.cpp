#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

bool match_p(const char& open, const char& close)
{
	if (open == '(' && close == ')') return true;
	if (open == '[' && close == ']') return true;
	if (open == '{' && close == '}') return true;
	if (open == '<' && close == '>') return true;
	return false;
}

char match_syntax(const char& open)
{
	switch (open) {
	case '(':
		return ')';
	case '[':
		return ']';
	case '{':
		return '}';
	case '<':
		return '>';
	default:
		return '?';
	}
}

std::map<char, int> score_errors(
	const std::vector<std::string>& lines,
	const std::map<char, int>& score_key
)
{
	std::stack<char> s{};
	std::map<char, int> hits{};
	for (auto& line : lines) {
		for (auto& c : line) {
			switch (c) {
			case '(':
			case '[':
			case '{':
			case '<':
				s.push(c);
				break;
			default:
				if (!match_p(s.top(), c)) {
					hits[c] += score_key.at(c);
				}
				s.pop();
				break;
			}
		}
	}
	return hits;
}

long long score_completion_string(const std::string& s, const std::map<char, int>& score_key)
{
	long long score{ 0 };
	for (const auto& c : s) {
		score *= 5;
		score += score_key.at(c);
	}
	return score;
}

std::vector<std::string> autocomplete(const std::vector<std::string>& lines)
{
	std::stack<char> s{};
	std::vector<std::string> completion_strings{};
	std::string completion{};
	bool corrupted{ false };
	for (const auto& l : lines) {
		while (!s.empty()) s.pop();
		completion = std::string{};
		corrupted = false;

		for (const auto& c : l) {
			switch (c) {
			case '(':
			case '[':
			case '{':
			case '<':
				s.push(c);
				break;
			default:
				if (!match_p(s.top(), c)) {
					corrupted = true;
				}
				s.pop();
				break;
			}
			if (corrupted) break;
		}
		if (corrupted) continue;

		while (!s.empty()) {
			completion += match_syntax(s.top());
			s.pop();
		}
		if (completion.length() > 0) {
			completion_strings.push_back(completion);
		}
	}

	return completion_strings;
}

void part1()
{
	std::vector<std::string> example{
		"[({(<(())[]>[[{[]{<()<>>",
		"[(()[<>])]({[<{<<[]>>(",
		"{([(<{}[<>[]}>{[]{[(<()>",
		"(((({<>}<{<{<>}{[]{[]{}",
		"[[<[([]))<([[{}[[()]]]",
		"[{[{({}]{}}([{[{{{}}([]",
		"{<[[]]>}<{[{[{[]{()[[[]",
		"[<(<(<(<{}))><([]([]()",
		"<{([([[(<>()){}]>(<<{{",
		"<{([{{}}[<[[[<>{}]]]>[]]"
	};

	std::vector<std::string> my_input{};
	std::ifstream is{ "input.txt" };
	std::string line{};
	while (std::getline(is, line)) {
		my_input.push_back(line);
	}

	std::map<char, int> score_key{
		{')', 3},
		{']', 57},
		{'}', 1197},
		{'>', 25137}
	};

	long long sum{ 0 };
	for (const auto& hit : score_errors(example, score_key)) {
		sum += hit.second;
	}
	std::cout << "Part 1 Example: " << sum << std::endl; //	26397

	sum = 0;
	for (const auto& hit : score_errors(my_input, score_key)) {
		sum += hit.second;
	}
	std::cout << "Part 1: " << sum << std::endl; // 464991
}

void part2()
{
	std::vector<std::string> example{
		"[({(<(())[]>[[{[]{<()<>>",
		"[(()[<>])]({[<{<<[]>>(",
		"{([(<{}[<>[]}>{[]{[(<()>",
		"(((({<>}<{<{<>}{[]{[]{}",
		"[[<[([]))<([[{}[[()]]]",
		"[{[{({}]{}}([{[{{{}}([]",
		"{<[[]]>}<{[{[{[]{()[[[]",
		"[<(<(<(<{}))><([]([]()",
		"<{([([[(<>()){}]>(<<{{",
		"<{([{{}}[<[[[<>{}]]]>[]]"
	};

	std::vector<std::string> my_input{};
	std::ifstream is{ "input.txt" };
	std::string line{};
	while (std::getline(is, line)) {
		my_input.push_back(line);
	}

	std::map<char, int> score_key{
		{')', 1},
		{']', 2},
		{'}', 3},
		{'>', 4}
	};


	std::vector<long long> scores{};
	for (auto& str : autocomplete(example)) {
		scores.push_back(score_completion_string(str, score_key));
	}
	std::sort(scores.begin(), scores.end());
	std::cout << "Part 2 Example: " << scores[scores.size() / 2] << std::endl; // 464991

	std::vector<long long> scores2{};
	for (auto& str : autocomplete(my_input)) {
		scores2.push_back(score_completion_string(str, score_key));
	}
	std::sort(scores2.begin(), scores2.end());
	std::cout << "Part 2: " 
		<< scores2[std::midpoint(0, static_cast<int>(scores2.size()))] 
		<< std::endl; // 3662008566
}

int main()
{
	part1();
	part2();
	return 0;
}