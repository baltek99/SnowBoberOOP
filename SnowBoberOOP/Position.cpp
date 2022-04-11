#include "Position.h"
class Position
{
private:
	int x;
	int y;

public:
	Position() {
		x = 0;
		y = 0;
	}

	Position(int x_, int y_) {
		x = x_;
		y = y_;
	}

	int getX() {
		return x;
	}

	void setX(int x_) {
		x = x_;
	}

	int getY() {
		return y;
	}

	void setY(int y_) {
		y = y_;
	}
};