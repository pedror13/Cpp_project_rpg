#include "PlayerHitbox.h"

PlayerHitbox::PlayerHitbox(sf::Sprite& sprite, float width, float height)
	:sprite(sprite)
{
	/*
		The hitbox has a slightly different coordenates for better colision with the texture
	*/

	this->hitboxCoords = sf::Vector2f(this->sprite.getPosition().x + 4.f, this->sprite.getPosition().y + 16.f);
	this->hitboxSize = sf::Vector2f(width - 8.f, height / 2 - 6.f);

	this->topRightCord = sf::Vector2f(this->hitboxCoords.x + this->hitboxSize.x, this->hitboxCoords.y);
	this->bottomRightCord = sf::Vector2f(this->hitboxCoords.x + this->hitboxSize.x, this->hitboxCoords.y + this->hitboxSize.y);

	this->hitbox.setPosition(this->hitboxCoords);
	this->hitbox.setSize(hitboxSize);
	this->hitbox.setOutlineThickness(-1.f);


}

PlayerHitbox::~PlayerHitbox()
{
}

sf::Vector2f & PlayerHitbox::GetHitboxTopRightCord()
{
	this->topRightCord = sf::Vector2f((this->hitboxCoords.x + this->hitboxSize.x), this->hitboxCoords.y);
	return this->topRightCord;
}

sf::Vector2f & PlayerHitbox::GetHitboxTopLeftCord()
{
	this->topLeftCord = sf::Vector2f(this->hitboxCoords.x, this->hitboxCoords.y);
	return this->topLeftCord;
}

sf::Vector2f & PlayerHitbox::GetHitboxBottomRightCord()
{
	this->bottomRightCord = sf::Vector2f((this->hitboxCoords.x + this->hitboxSize.x), (this->hitboxCoords.y + this->hitboxSize.y));
	return this->bottomRightCord;
}

sf::Vector2f & PlayerHitbox::GetHitboxBottomLeftCord()
{
	this->bottomLeftCord = sf::Vector2f(this->hitboxCoords.x, (this->hitboxCoords.y + this->hitboxSize.y));
	return this->bottomLeftCord;
}

void PlayerHitbox::update()
{
	this->hitboxCoords = sf::Vector2f(this->sprite.getPosition().x + 4, this->sprite.getPosition().y + 16.f);
	this->hitbox.setPosition(this->hitboxCoords);

}

void PlayerHitbox::render(sf::RenderTarget & target)
{

}