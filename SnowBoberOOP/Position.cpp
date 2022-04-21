#include "Position.h"

Position::Position() : x(0), y(0) {}

Position::Position(float x_, float y_) : x(x_), y(y_) {}

float Position::getX() const {
	return x;
}

void Position::setX(float x_) {
	x = x_;
}

float Position::getY() const {
	return y;
}

void Position::setY(float y_) {
	y = y_;
}