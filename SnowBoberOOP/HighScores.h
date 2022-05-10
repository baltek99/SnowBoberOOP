#pragma once
#include <vector>
#include "ResultBind.h"

class HighScores
{
private:
	// zamieni� na deque
	std::vector<ResultBind> scores;
	const int maxNumberOfResults;

	void bubbleSort(std::vector<ResultBind>& arr);

public :
	HighScores();

	std::vector<ResultBind> getScores() const;

	void addResult(const std::string name, int score);

	void readHighScores();

	void writeHighScores();
};

