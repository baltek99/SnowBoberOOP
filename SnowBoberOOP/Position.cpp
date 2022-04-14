#include "Position.h"

Position::Position() : x(0), y(0) {}

Position::Position(int x_, int y_) : x(x_), y(y_) {}

int Position::getX() const {
	return x;
}

void Position::setX(int x_) {
	x = x_;
}

int Position::getY() const {
	return y;
}

void Position::setY(int y_) {
	y = y_;
}