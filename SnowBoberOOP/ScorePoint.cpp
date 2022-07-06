#include "ScorePoint.h"

ScorePoint::ScorePoint(const Position &position_, int speed_) :
	Obstacle(position_, Visual(TexturesManager::rail, ConstValues::SCORE_WIDTH, ConstValues::SCORE_HEIGHT), speed_, ObstacleType::SCORE_POINT) {
	collisionInfo = CollisionInfo(1, ConstValues::SCORE_HEIGHT);
}

void ScorePoint::collide(ICollidable *object) {
}
