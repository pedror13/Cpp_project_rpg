#pragma once
#include "../Headers/Entity.h"

class Player :
	public Entity
{
private:
	//Variables
	sf::Vector2f playerPos;
	sf::Vector2f playerSize;

	///Hitbox Components
	PlayerHitbox* playerHitbox;
	sf::Vector2f topLeftCord;
	sf::Vector2f topRightCord;
	sf::Vector2f bottomLeftCord;
	sf::Vector2f bottomRightCord;

	//Private Functions
	void initVariables();
	void initComponents();

public:

	//Constructors & Destructors
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	//Functions
	///Access functions
	sf::Vector2f getPlayerPos();
	sf::Vector2f getPlayerSize();
	sf::Vector2f& getTopLeftCord();
	sf::Vector2f& getTopRightCord();
	sf::Vector2f& getBottomLeftCord();
	sf::Vector2f& getBottomRightCord();

	///Update functions
	virtual void update(const float& dt);
};
