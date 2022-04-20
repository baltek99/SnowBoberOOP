#pragma once

#include <SFML/Graphics.hpp>

class TexturesManager
{
public :
    sf::Texture background;
    sf::Texture start;
    sf::Texture gameOver;
    sf::Texture highScores;
    sf::Texture boberStand;
    sf::Texture boberCrouch;
    sf::Texture boberJump;
    sf::Texture boberFlip;
    sf::Texture boberSlide;
    sf::Texture box;
    sf::Texture rail;
    sf::Texture pipe;
    sf::Texture grid;
    sf::Texture gridStick;
    sf::Texture heart;

    TexturesManager();
};

