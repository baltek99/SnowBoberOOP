#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class IRenderable {
public :
	virtual void render(sf::RenderWindow& window) = 0;
};
