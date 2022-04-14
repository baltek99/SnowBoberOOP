#include "Entity.h"

Entity::Entity() {
	position = Position(0, 0);
}

Entity::Entity(const Position &position_) {
	position = position_;
}

Position Entity::getPosition() const {
	return position;
}

Entity::~Entity()
{
}

