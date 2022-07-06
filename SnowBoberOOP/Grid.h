#pragma once

#include "Obstacle.h"

class Grid : public Obstacle {
public :
    Grid(const Position &position_, int speed_);

    void collide(ICollidable *object) override;
};
