#include "Entity.h"

/*
----------Private Functions----------
*/
void Entity::initVariables()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;

	if (!this->font.loadFromFile("Resources/Fonts/lastfontwastingonyou.ttf"))
	{
		throw("ERROR::PrimaryMenuInstance::COULD NOT LOAD FONT");
	}

}

/*
----------Constructors & Destructors----------
*/
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

/*
----------Functions----------
*/
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::creatMovementComponent(const float maxSpeed, const float acceleration, const float deceleration)
{
	this->movementComponent = new PlayerMovement(this->sprite, maxSpeed, acceleration, deceleration);
}

void Entity::creatAnimationComponent(sf::Texture & textureSheet)
{
	this->animationComponent = new PlayerAnimation(this->sprite, textureSheet);
}

PlayerHitbox Entity::creatHitboxComponent(sf::Sprite & sprite, float width, float height)
{
	this->hitboxComponent = new PlayerHitbox(sprite, width, height);
	return *this->hitboxComponent;
}

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

const sf::Vector2f& Entity::getPos() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f & Entity::getSize() const
{
	return sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
}

sf::Vector2f Entity::updatePosSprite(const float & dt)
{
	//Updating the Player position
	this->spritePos = getPos();
	return this->spritePos;
}

void Entity::move(const float directionX, const float directionY, const float& dt)
{
	/*Moves the entity in a given direction and speed*/

	if (this->movementComponent)
	{
		this->movementComponent->move(directionX, directionY, dt);
	}
}

sf::Vector2f & Entity::updHitboxTopRightCord(const float & dt)
{
	this->topRightCord = hitboxComponent->GetHitboxTopRightCord();
	return this->topRightCord;
}

sf::Vector2f & Entity::updHitboxTopLeftCord(const float & dt)
{
	this->topLeftCord = hitboxComponent->GetHitboxTopLeftCord();
	return this->topLeftCord;
}

sf::Vector2f & Entity::updHitboxBottomRightCord(const float & dt)
{
	this->bottomRightCord = hitboxComponent->GetHitboxBottomRightCord();
	return this->bottomRightCord;
}

sf::Vector2f & Entity::updHitboxBottomLeftCord(const float & dt)
{
	this->bottomLeftCord = hitboxComponent->GetHitboxBottomLeftCord();
	return this->bottomLeftCord;
}

void Entity::FinishMovement()
{
	this->movementComponent->FinishMovement();
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
