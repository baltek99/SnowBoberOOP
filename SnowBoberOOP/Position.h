#pragma once
#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	Position();

	Position(int x_, int y_);

	int getX();

	void setX(int x_);

	int getY();

	void setY(int y_);
};
#endif // !POSITION_H

