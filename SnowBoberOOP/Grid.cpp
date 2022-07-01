#include "Grid.h"
#include "Player.h"

Grid::Grid(const Position &position_, int speed_) :
	Obstacle(position_, Visual(TexturesManager::grid, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT), speed_, ObstacleType::GRID) {
	zIndex = 1;
	collisionInfo = CollisionInfo(168, 350);
}

void Grid::collide(ICollidable *object) {
	Player* player = static_cast<Player*>(object);

	if (player->getPlayerState() != PlayerState::CROUCH) {
		getVisual().setTexture(TexturesManager::gridBroken);
	}
}