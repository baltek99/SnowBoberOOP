#pragma once

#include "EntityWithTexture.h"
#include "IMovable.h"
#include "ICollidable.h"
#include "CollisionInfo.h"
#include "ObstacleType.h"
#include "ConstValues.h"

class Obstacle : public EntityWithTexture, public IMovable, public ICollidable {
protected:
    CollisionInfo collisionInfo;
    ObstacleType obstacleType;
    int speed;

public:
    Obstacle(const Position &position, const Visual &visual, int speed, const ObstacleType obstacleType_);

    CollisionInfo getCollisionInfo() const;

    ObstacleType getObstacleType() const;

    void speedUp(long gameFrame) override;

    void move(long gameFrame) override;

};

