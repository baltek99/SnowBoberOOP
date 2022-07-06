#pragma once
#include "Position.h"

class Entity {
protected:
	Position position;

public:
	Entity();

	Entity(const Position &pos);

	Position getPosition() const;
	
	Position& getPosition();

	virtual ~Entity();
};
