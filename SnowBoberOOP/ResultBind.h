#pragma once

#include <string>

class ResultBind {

private :
	const std::string name;
	const int score;

public :
	ResultBind(const std::string name_, int score_);

	std::string getName() const;

	int getScore() const;

	std::string toString() const;

	int compareTo(const ResultBind& result) const;
};

