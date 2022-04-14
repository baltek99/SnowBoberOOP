#pragma once

#include "Obstacle.h"

class Grid : Obstacle
{
public :
    Grid(const Position &position_, int speed_);

    void collide(ICollidable &object) override;
};

