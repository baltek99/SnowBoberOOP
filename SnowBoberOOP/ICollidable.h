#pragma once

class ICollidable {
public :
	virtual void collide(ICollidable &object) = 0;
};
