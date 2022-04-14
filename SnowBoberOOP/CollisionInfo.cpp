#include "CollisionInfo.h"

CollisionInfo::CollisionInfo() {
    rectangle = sf::IntRect();
    collisionType = CollisionType::NONE;
}

CollisionInfo::CollisionInfo(int width, int height) {
    rectangle = sf::IntRect();
    rectangle.width = width;
    rectangle.height = height;
    collisionType = CollisionType::NONE;
}
