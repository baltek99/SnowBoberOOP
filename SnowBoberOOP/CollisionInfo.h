#pragma once

#include "CollisionType.h"
#include <SFML/Graphics.hpp>

class CollisionInfo
{
public :
    sf::IntRect rectangle;
    CollisionType collisionType;

    CollisionInfo();

    CollisionInfo(int width, int height);
};

