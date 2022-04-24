#pragma once
#include <vector>
#include "ResultBind.h"

class HighScores
{
private:
	// zamieniæ na deque
	std::vector<ResultBind> scores;
	const int maxNumberOfResults;

public :
	HighScores();

	std::vector<ResultBind> getScores() const;

	void addResult(const std::string name, int score);

	void bubbleSort(std::vector<ResultBind>& arr);

	void readHighScores();

	void writeHighScores();
};

