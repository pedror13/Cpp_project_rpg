#include "../Headers/PlayerMovement.h"

/*
----------Constructors & Destructors----------
*/
PlayerMovement::PlayerMovement(sf::Sprite& sprite, float maxSpeed,
	float acceleration, float deceleration)
	: sprite(sprite), maxSpeed(maxSpeed), acceleration(acceleration), deceleration(deceleration)
{

}

PlayerMovement::~PlayerMovement()
{

}

/*
----------Functions----------
*/

const short int PlayerMovement::getDirectionCharMov() const
{
	//Idle
	if (this->speed.x == 0.f && this->speed.y == 0.f)
	{
		return 0;
	}

	//Moving -> down
	if (this->speed.y > 0.f)
	{
		return 1;
	}

	//Moving -> right
	if (this->speed.x > 0.f)
	{
		return 2;
	}

	//Moving -> up
	if (this->speed.y < 0.f)
	{
		return 3;
	}

	//Moving -> left
	if (this->speed.x < 0.f)
	{
		return 4;
	}
}

void PlayerMovement::FinishMovement()
{
	this->speed.x = 0.f;
	this->speed.y = 0.f;
}

const sf::Vector2f & PlayerMovement::getVelocity() const
{
	return this->speed;
}

void PlayerMovement::update(const float & dt)
{
	//Decelaration X
	if (this->speed.x > 0.f)
	{
		if (this->speed.x > this->maxSpeed)
		{
			this->speed.x = this->maxSpeed;
		}

		this->speed.x -= deceleration;
		if (this->speed.x < 0.f)
		{
			this->speed.x = 0.f;
		}
	}
	else if (this->speed.x < 0.f)
	{
		if (this->speed.x < -this->maxSpeed)
		{
			this->speed.x = -this->maxSpeed;
		}

		this->speed.x += deceleration;
		if (this->speed.x > 0.f)
		{
			this->speed.x = 0.f;
		}
	}

	//Decelaration Y
	if (this->speed.y > 0.f)
	{
		if (this->speed.y > this->maxSpeed)
		{
			this->speed.y = this->maxSpeed;
		}

		this->speed.y -= deceleration;
		if (this->speed.y < 0.f)
		{
			this->speed.y = 0.f;
		}
	}
	else if (this->speed.y < 0.f)
	{
		if (this->speed.y < -this->maxSpeed)
		{
			this->speed.y = -this->maxSpeed;
		}

		this->speed.y += deceleration;
		if (this->speed.y > 0.f)
		{
			this->speed.y = 0.f;
		}
	}

	//Final movement
	this->sprite.move(this->speed * dt);
}

void PlayerMovement::move(const float directionX, const float directionY, const float& dt)
{
	//Accelaration
	this->speed.x += this->acceleration * directionX;

	this->speed.y += this->acceleration * directionY;

}