#include "HighScores.h"

HighScores::HighScores() : maxNumberOfResults(10), scores(std::vector<ResultBind>()) {}

std::vector<ResultBind> HighScores::getScores() const {
	return scores;
}

void HighScores::addResult(const std::string name, int score) {
	scores.push_back(ResultBind(name, score));

	//sort

	if (scores.size() > maxNumberOfResults) {
		//scores.
	}
}