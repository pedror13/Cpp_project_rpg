#pragma once
#include "PlayerMovement.h"
#include "PlayerAnimation.h"
#include "PlayerHitbox.h"

class Entity
{
private:
	//Private Functions
	void initVariables();

protected:
	//Variables
	sf::Sprite sprite;
	//sf::FloatRect spriteHitbox;

	sf::Vector2f spritePos;
	sf::Font font; // Temporary ( DEBUG )

	PlayerMovement* movementComponent;
	PlayerAnimation* animationComponent;
	PlayerHitbox* hitboxComponent;

	//Hitbox Components
	sf::Vector2f topLeftCord;
	sf::Vector2f topRightCord;
	sf::Vector2f bottomLeftCord;
	sf::Vector2f bottomRightCord;

public:
	//Constructors & Destructors
	Entity();
	virtual ~Entity();


	//Functions
	void setTexture(sf::Texture& texture);
	void creatMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);
	void creatAnimationComponent(sf::Texture& textureSheet);
	PlayerHitbox creatHitboxComponent(sf::Sprite& sprite, float width, float height);

	const sf::Vector2f& getPos() const;
	const sf::Vector2f& getSize() const;
	sf::Vector2f updatePosSprite(const float& dt);
	//bool checkIntersect(const sf::FloatRect& frect);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float&dt);

	sf::Vector2f& updHitboxTopRightCord(const float & dt);
	sf::Vector2f& updHitboxTopLeftCord(const float & dt);
	sf::Vector2f& updHitboxBottomRightCord(const float & dt);
	sf::Vector2f& updHitboxBottomLeftCord(const float & dt);

	void FinishMovement();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};