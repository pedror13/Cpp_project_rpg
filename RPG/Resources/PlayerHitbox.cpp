#include "PlayerHitbox.h"

PlayerHitbox::PlayerHitbox(sf::Sprite& sprite, float width, float height)
	:sprite(sprite)
{
	this->hitboxCoords = sf::Vector2f(this->sprite.getPosition().x + 4.f, this->sprite.getPosition().y + 16.f);
	this->hitboxSize = sf::Vector2f(width - 8.f, height / 2 - 6.f);

	this->topRightCord = sf::Vector2f(this->hitboxCoords.x + this->hitboxSize.x, this->hitboxCoords.y);
	this->bottomRightCord = sf::Vector2f(this->hitboxCoords.x + this->hitboxSize.x, this->hitboxCoords.y + this->hitboxSize.y);

	this->hitbox.setPosition(this->hitboxCoords);
	this->hitbox.setSize(hitboxSize);
	this->hitbox.setOutlineThickness(-1.f);
	//TODO REMOVE LATER (DEBUG)
	//this->hitbox.setFillColor(sf::Color::Transparent);
	//this->hitbox.setOutlineColor(sf::Color::Magenta);

}

PlayerHitbox::~PlayerHitbox()
{
}


sf::Vector2f PlayerHitbox::getPos()
{
	return sf::Vector2f(this->hitboxCoords.x, this->hitboxCoords.y);
}

sf::Vector2f PlayerHitbox::getSize()
{
	return  sf::Vector2f(this->hitboxSize.x, this->hitboxSize.y);
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


bool PlayerHitbox::checkForIntersection(const sf::FloatRect & frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void PlayerHitbox::ChangeHitboxCoords(const float x, const float y)
{
	this->hitbox.setPosition(this->hitbox.getPosition().x + x, this->hitbox.getPosition().y + y);
}


void PlayerHitbox::update()
{
	this->hitboxCoords = sf::Vector2f(this->sprite.getPosition().x + 4, this->sprite.getPosition().y + 16.f);
	//this->hitboxSize = sf::Vector2f(this->hitbox.getGlobalBounds().width, this->hitbox.getGlobalBounds().height);
	this->hitbox.setPosition(this->hitboxCoords);

	//std::cout << "HitBOX postions is = " << hitbox.getPosition().x + hitboxSize.x << ", " << hitbox.getPosition().y; //TODO REMOVE LATER (DEBUG)
}


void PlayerHitbox::render(sf::RenderTarget & target)
{
	//(DEBUG)
	//target.draw(this->hitbox);
}