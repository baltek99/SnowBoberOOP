#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"

class Entity
{
protected:
	Position position;

public:
	Entity();

	Entity(const Position &pos);

	Position getPosition() const;

	virtual ~Entity();
};
#endif // !ENTITY_H

