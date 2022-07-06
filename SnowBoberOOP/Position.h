#pragma once

class Position {
private:
	float x;
	float y;

public:
	Position();

	Position(float x_, float y_);

	float getX() const;

	void setX(float x_);

	float getY() const;

	void setY(float y_);
};
