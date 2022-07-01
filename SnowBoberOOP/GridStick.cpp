#include "GridStick.h"
#include "Player.h"

GridStick::GridStick(const Position &position_, int speed_) :
	Obstacle(position_, Visual(TexturesManager::gridStick, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT), speed_, ObstacleType::GRID_STICK) {
	collisionInfo = CollisionInfo(168, 350);
}

void GridStick::collide(ICollidable *object) {
	Player* player = static_cast<Player*>(object);

	if (player->getPlayerState() != PlayerState::CROUCH) {
		getVisual().getSprite().setScale(0, 0);
	}
}