#pragma once

#include <ctime>
#include <iostream>
#include <sstream>		

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class Button
{
private:
	//Variables
	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Texture buttonTexture;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	//Constructors & Destructors
	Button(float x, float y, float witdth, float height,
		sf::Font* font, std::string text, sf::Texture* buttonTexture,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	~Button();

	//Functions
	const bool isPressed() const;
	void update(const sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);
};