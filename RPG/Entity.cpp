#include "Entity.h"

/*
----------Private Functions----------
*/
void Entity::initVariables()
{
	this->movementComponent = nullptr;
	if (!this->font.loadFromFile("Fonts/lastfontwastingonyou.ttf"))
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

void Entity::creatAnimationComponent( sf::Texture & textureSheet)
{
	this->animationComponent = new PlayerAnimation(this->sprite, textureSheet);
}

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

const sf::Vector2f& Entity::getPos() const
{
	return this->sprite.getPosition();
}

sf::Vector2f Entity::updatePosSprite(const float & dt)
{
	//Updating the Player position
	this->spritePos = getPos();
	std::cout << "Player postions is = " << spritePos.x << ", " << spritePos.y; //TODO REMOVE LATER (DEBUG)
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

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget* target)
{	
	target->draw(this->sprite);

	//TODO REMOVE LATER ( DEBUG )
	sf::Text playerText;
	playerText.setPosition(this->spritePos.x, this->spritePos.y+27);
	playerText.setCharacterSize(20);
	playerText.setFont(this->font);
	std::stringstream ss;
	ss <<std::setprecision(4)<< this->spritePos.x << ", " << this->spritePos.y;
	playerText.setString(ss.str());
	target->draw(playerText);
}
