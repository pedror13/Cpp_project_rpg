#include "Player.h"

/*
----------Private Functions----------
*/
void Player::initVariables()
{
}

void Player::initComponents()
{

}

/*
----------Constructors & Destructors----------
*/
Player::Player(float x, float y, sf::Texture& textureSheet)
{
	this->initVariables();
	this->setPosition(x, y);
	this->creatMovementComponent(60.f, 30.f, 20.f);
	this->creatAnimationComponent(textureSheet);
	this->playerHitbox = &this->creatHitboxComponent(this->sprite, 16.f, 32.f);
	this->playerSize = getSize();


	//TODO CHECK DECELERATING FUNCTION

	this->animationComponent->addAnimation("IDLE", 30.f, 0, 0, 3, 0, 16, 32); // TODO ADD THE IDLE CHECK WITH THE IDLE FUNCTION
	this->animationComponent->addAnimation("WALKING DOWN", 15.f, 0, 0, 3, 0, 16, 32);
	this->animationComponent->addAnimation("WALKING RIGHT", 15.f, 0, 1, 3, 1, 16, 32);
	this->animationComponent->addAnimation("WALKING UP", 15.f, 0, 2, 3, 2, 16, 32);
	this->animationComponent->addAnimation("WALKING LEFT", 15.f, 0, 3, 3, 3, 16, 32);
}

Player::~Player()
{

}

/*
----------Functions----------
*/

sf::Vector2f Player::getPlayerPos()
{
	return this->playerPos;
}

sf::Vector2f Player::getPlayerSize()
{
	return this->playerSize;
}

sf::Vector2f & Player::getTopLeftCord()
{
	return this->topLeftCord;
}

sf::Vector2f & Player::getTopRightCord()
{
	return this->topRightCord;
}

sf::Vector2f & Player::getBottomLeftCord()
{
	return this->bottomLeftCord;
}

sf::Vector2f & Player::getBottomRightCord()
{
	return this->bottomRightCord;
}

void Player::update(const float & dt)
{
	/*
		Main update function of this class
		Update all motion values and set the animation for that
	*/

	this->movementComponent->update(dt);
	this->playerPos = updatePosSprite(dt);
	this->hitboxComponent->update();
	this->topRightCord = updHitboxTopRightCord(dt);
	this->topLeftCord = updHitboxTopLeftCord(dt);
	this->bottomRightCord = updHitboxBottomRightCord(dt);
	this->bottomLeftCord = updHitboxBottomLeftCord(dt);

	/*0 -> IDLE
	  1 -> MOVING DOWN
	  2 -> MOVING RIGHT
	  3 -> MOVING UP
	  4 -> MOVING LEFT
	 */

	if (this->movementComponent->getDirectionCharMov() == 0)
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getDirectionCharMov() == 1)
	{
		this->animationComponent->play("WALKING DOWN", dt);
	}
	else if (this->movementComponent->getDirectionCharMov() == 2)
	{
		this->animationComponent->play("WALKING RIGHT", dt);
	}
	else if (this->movementComponent->getDirectionCharMov() == 3)
	{
		this->animationComponent->play("WALKING UP", dt);
	}
	else if (this->movementComponent->getDirectionCharMov() == 4)
	{
		this->animationComponent->play("WALKING LEFT", dt);
	}
}