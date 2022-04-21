#include "Grid.h"

Grid::Grid(const Position &position_, int speed_) :
	Obstacle(position_, Visual(TexturesManager::grid, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT), speed_, ObstacleType::GRID) {
	zIndex = 1;
	collisionInfo = CollisionInfo(168, 350);
}

void Grid::collide(ICollidable *object) {}