#pragma once

#include <string>

class ResultBind {
private:
	std::string name;
	int score;
public:
	ResultBind();

	ResultBind(const std::string name_, int score_);

	bool operator < (ResultBind& r);

	std::string getName() const;

	int getScore() const;

	std::string toString() const;

	int compareTo(const ResultBind& result) const;

	friend std::ostream& operator << (std::ostream& out, const ResultBind& obj);

	friend std::istream& operator >> (std::istream& in, ResultBind& obj);
};
