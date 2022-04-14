#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Y {
public:
    int i;

    Y() : i(0) {}
};

class X {
private:
    Y y;
public:
    X() : y(Y()) {}

    Y const& getY() const {
        return y;
    }
};


int main()
{
    //sf::RenderWindow window(sf::VideoMode(600, 600), "sfml works!");
    //sf::CircleShape shape(300.f);
    //shape.setFillColor(sf::Color::Green);

    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    window.clear();
    //    window.draw(shape);
    //    window.display();
    //}

    X x = X();

    //Y& y = x.getY();

    //y.i = 10;

    //std::cout << y.i;

    return 0;
}

