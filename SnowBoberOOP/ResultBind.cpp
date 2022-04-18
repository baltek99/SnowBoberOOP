#include "ResultBind.h"


ResultBind::ResultBind(const std::string name_, int score_) : name(name_), score(score_) {}

std::string ResultBind::getName() const {
	return name;
}

int ResultBind::getScore() const {
	return score;
}

std::string ResultBind::toString() const {
	return name + " : " + std::to_string(score);
}

int ResultBind::compareTo(const ResultBind& result) const {
	return score > result.getScore();
}
