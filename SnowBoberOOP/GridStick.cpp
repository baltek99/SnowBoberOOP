#include "GridStick.h"
#include "ConstValues.h"

GridStick::GridStick(const Position &position_, int speed_) :
	Obstacle(position_, Visual(TexturesManager::gridStick, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT), speed_, ObstacleType::GRID) {
	collisionInfo = CollisionInfo(0, 0);
}

void GridStick::collide(ICollidable *object) {}