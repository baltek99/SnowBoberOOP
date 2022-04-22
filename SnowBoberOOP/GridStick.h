#pragma once

#include "Obstacle.h"

class GridStick : public Obstacle {
public :
    GridStick(const Position &position_, int speed_);

    void collide(ICollidable *object) override;
};

