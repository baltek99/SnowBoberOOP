#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "sfml works!");
    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Green);
    
    sf::Sprite sprite;
   
    sf::Texture texture;
    texture.loadFromFile("assets/bober-stand.png");
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

