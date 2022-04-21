#pragma once

#include "Obstacle.h"

class ScorePoint : public Obstacle {
public :
    ScorePoint(const Position &position_, int speed_);

    void collide(ICollidable *object) override;
};

