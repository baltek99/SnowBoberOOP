#include "HighScores.h"
#include <fstream>
#include <algorithm>

HighScores::HighScores() : maxNumberOfResults(10), scores(std::vector<ResultBind>()) {}

std::vector<ResultBind> HighScores::getScores() const {
	return scores;
}

void HighScores::addResult(const std::string name, int score) {
	scores.push_back(ResultBind(name, score));

	std::sort(scores.begin(), scores.end());

	if (scores.size() > maxNumberOfResults) {
		scores.erase(scores.begin());
	}
}

void HighScores::readHighScores() {
	std::ifstream in("highscores.txt");

	int number_of_lines = 0;
	std::string line;

	while (std::getline(in, line))
		++number_of_lines;
	in.close();

	std::ifstream in2("highscores.txt");
	if (number_of_lines % 2 == 0) {
		for (int i = 0; i < number_of_lines / 2; i++) {
			ResultBind rb;
			in2 >> rb;
			scores.push_back(rb);
		}
	}
	in2.close();

	std::sort(scores.begin(), scores.end());
}

void HighScores::writeHighScores() {
	std::ofstream out;
	out.open("highscores.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < scores.size(); i++) {
		out << scores.at(i);
	}
	out.close();
}
