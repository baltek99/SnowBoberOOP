#include "TextBox.h"

TextBox::TextBox() {
	isSelected = false;
	hasLimit = false;
	limit = 0;
}

TextBox::TextBox(int size, sf::Color color, bool sel) {
	textBox.setCharacterSize(size);
	textBox.setFillColor(color);
	isSelected = sel;
	hasLimit = false;
	limit = 0;
	if (sel) {
		textBox.setString("_");
	}
	else {
		textBox.setString("");
	}
}

void TextBox::setFont(sf::Font& font) {
	textBox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos) {
	textBox.setPosition(pos);
}

void TextBox::setLimit(bool boo) {
	hasLimit = boo;
}

void TextBox::setLimit(bool boo, int lim) {
	hasLimit = boo;
	limit = lim;
}

void TextBox::setSelected(bool sel) {
	isSelected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		textBox.setString(newT);
	}
}

std::string TextBox::getText() const {
	return text.str();
}

void TextBox::draw(sf::RenderWindow& window) {
	window.draw(textBox);
}

void TextBox::typedOn(sf::Event input) {
	if (isSelected) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit && text.str().length() <= limit) {
				inputLogic(charTyped);
			}
			else if (!hasLimit) {
				inputLogic(charTyped);
			}
		}
	}
}

void TextBox::inputLogic(int charTyped) {
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textBox.setString(text.str() + "_");
}

void TextBox::deleteLastChar() {
	std::string t = text.str();
	std::string newT = "";

	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	textBox.setString(text.str());
}