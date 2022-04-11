#include "Entity.h"

class Entity
{
protected:
	Position position;

public:
	Entity() {
		position = Position(0, 0);
	}

	Entity(Position pos) {
		position = pos;
	}

	Position getPosition() {
		return position;
	}

	virtual ~Entity() {}
};

