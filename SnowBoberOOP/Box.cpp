#include "Box.h"
#include "ConstValues.h"

Box::Box(const Position &position_, int speed_) : 
	Obstacle(position_, Visual(TexturesManager::box, ConstValues::BOX_WIDTH, ConstValues::BOX_HEIGHT), speed_, ObstacleType::BOX) {}

void Box::collide(ICollidable *object) {}
