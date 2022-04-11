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

	Entity(Position pos);

	Position getPosition();

	virtual ~Entity();
};
#endif // !ENTITY_H

