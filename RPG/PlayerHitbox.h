#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class PlayerHitbox
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::Vector2f hitboxCoords;
	sf::Vector2f hitboxSize;

	sf::Vector2f topLeftCord;
	sf::Vector2f topRightCord;
	sf::Vector2f bottomLeftCord;
	sf::Vector2f bottomRightCord;
public:

	//Functions
	PlayerHitbox(sf::Sprite& sprite, float width, float height);
	~PlayerHitbox();

	sf::Vector2f getPos();
	sf::Vector2f getSize();

	sf::Vector2f& GetHitboxTopRightCord();
	sf::Vector2f& GetHitboxTopLeftCord();
	sf::Vector2f& GetHitboxBottomRightCord();
	sf::Vector2f& GetHitboxBottomLeftCord();

	bool checkForIntersection(const sf::FloatRect& frect);
	void ChangeHitboxCoords(const float x, const float y);

	void update();

	void render(sf::RenderTarget& target);
};