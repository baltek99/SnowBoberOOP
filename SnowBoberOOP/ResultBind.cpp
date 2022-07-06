#include "ResultBind.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

ResultBind::ResultBind() : name(""), score(0) {
}

ResultBind::ResultBind(const std::string name_, int score_) : name(name_), score(score_) {
}

std::string ResultBind::getName() const {
	return name;
}

int ResultBind::getScore() const {
	return score;
}

std::string ResultBind::toString() const {
	return name + " : " + std::to_string(score);
}

bool ResultBind::operator < (ResultBind& r) {
	return this->score < r.score;
}

int ResultBind::compareTo(const ResultBind& result) const {
	return score > result.getScore();
}

std::ostream& operator << (std::ostream& out, const ResultBind& obj) {
	out << obj.name << "\n" << obj.score << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, ResultBind& obj) {
	in >> obj.name;
	in >> obj.score;

	return in;
}
