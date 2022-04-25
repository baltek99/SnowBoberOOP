#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
private:
	sf::Text textBox;
	std::ostringstream text;
	bool isSelected;
	bool hasLimit;
	int limit;

public :
	TextBox();

	TextBox(int size, sf::Color color, bool sel);

	void setFont(sf::Font& font);

	void setPosition(sf::Vector2f pos);

	void setLimit(bool boo);

	void setLimit(bool boo, int lim);

	void setSelected(bool sel);

	std::string getText() const;

	void draw(sf::RenderWindow& window);

	void typedOn(sf::Event input);

	void inputLogic(int charTyped);

	void deleteLastChar();
};

