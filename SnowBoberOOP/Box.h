#pragma once

#include "Obstacle.h"

class Box : public Obstacle {
public :
	Box(const Position &position_, int speed_);

	void collide(ICollidable *object) override;
};
