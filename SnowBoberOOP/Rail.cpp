#include "Rail.h"
#include "ConstValues.h"

Rail::Rail(const Position &position_, int speed_) :
	Obstacle(position_, Visual(TexturesManager::rail, ConstValues::RAIL_WIDTH, ConstValues::RAIL_HEIGHT), speed_, ObstacleType::RAIL) {
	collisionInfo = CollisionInfo(ConstValues::RAIL_WIDTH - 35, ConstValues::RAIL_HEIGHT);
}

void Rail::setRailCollisionHeight(int height) {
	collisionInfo = CollisionInfo(ConstValues::RAIL_WIDTH, height);
}

void Rail::collide(ICollidable* object) {}