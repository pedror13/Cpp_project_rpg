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
		sf::Font* font, std::string text, int textSize,
		sf::Texture* buttonTexture,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Functions
	///Access functions
	sf::Vector2f getPosition();
	sf::Vector2f getLength();

	///Update functions
	void update(const sf::Vector2f mousePosition);
	const bool isPressed() const;
	const bool isHovered() const;

	///Render functions
	void render(sf::RenderTarget& target);
};