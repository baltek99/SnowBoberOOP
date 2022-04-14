#pragma once

class IMovable {
public :
	virtual void move(long gameFrame) = 0;
	virtual void speedUp(long gameFrame) = 0;
};

