#include "Obstacle.h"

Obstacle::Obstacle(const Position& position_, const Visual& visual_, int speed_, ObstacleType obstacleType_) : EntityWithTexture(position_, visual_), speed(speed_), obstacleType(obstacleType_) {
    collisionInfo = CollisionInfo(visual_.getSprite().getTextureRect());
}

CollisionInfo Obstacle::getCollisionInfo() const {
    return collisionInfo;
}

ObstacleType Obstacle::getObstacleType() const {
    return obstacleType;
}

void Obstacle::speedUp(long gameFrame) {
    if (gameFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
        speed--;
    }
}

void Obstacle::move(long gameFrame) {
    position.setX(position.getX() + speed);
}
