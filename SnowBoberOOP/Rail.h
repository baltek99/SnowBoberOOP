#pragma once

#include "Obstacle.h"

class Rail : public Obstacle
{
public :
    Rail(const Position &position_, int speed_);

    void setRailCollisionHeight(int height);
    
    void collide(ICollidable &object) override;
};

