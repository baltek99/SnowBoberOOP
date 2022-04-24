#include "HighScores.h"
#include <fstream>

HighScores::HighScores() : maxNumberOfResults(10), scores(std::vector<ResultBind>()) {}

std::vector<ResultBind> HighScores::getScores() const {
	return scores;
}

void HighScores::addResult(const std::string name, int score) {
	scores.push_back(ResultBind(name, score));

	//sort
	bubbleSort(scores);

	if (scores.size() > maxNumberOfResults) {
		scores.erase(scores.begin());
	}
}

void HighScores::bubbleSort(std::vector<ResultBind>& arr) {
	for (int i = 0; i < arr.size() - 1; i++)
		for (int j = 0; j < arr.size() - i - 1; j++)
			if (arr[j].compareTo(arr[j + 1]))
				std::swap(arr[j], arr[j + 1]);
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

	bubbleSort(scores);
}

void HighScores::writeHighScores() {
	std::ofstream out;
	out.open("highscores.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < scores.size(); i++) {
		out << scores.at(i);
	}
	out.close();
}