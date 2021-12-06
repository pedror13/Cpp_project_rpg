#include "PlayerAnimation.h"

/*
----------Constructors & Destructors----------
*/

PlayerAnimation::PlayerAnimation(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{

}

PlayerAnimation::~PlayerAnimation()
{
	for (auto &i : animations)
	{
		delete i.second;
	}
}

/*
----------Functions----------
*/

void PlayerAnimation::addAnimation(const std::string key, float speed,
	int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, speed, startFrameX, startFrameY, framesX, framesY, width, height);
}

void PlayerAnimation::play(const std::string key, const float & dt)
{
	this->animations[key]->play(dt);
}

