#pragma once

#include "Obstacle.h"

class GridStick : Obstacle {
public :
    GridStick(const Position &position_, int speed_);

    void collide(ICollidable *object) override;
};

