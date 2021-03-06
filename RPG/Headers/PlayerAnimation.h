#pragma once

#include <iostream>
#include <map>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class PlayerAnimation
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float speed;
		float timer;
		int width;
		int height;
		sf::IntRect startRec;
		sf::IntRect currentRec;
		sf::IntRect endRec;

		//Constructor & Destructor
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float speed,
			int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
			: sprite(sprite), textureSheet(textureSheet),
			speed(speed), width(width), height(height)
		{
			this->timer = 0.f;
			this->startRec = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currentRec = this->startRec;
			this->endRec = sf::IntRect(framesX * width, framesY * height, width, height);
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRec);
		}

		//Functions
		void play(const float& dt)
		{
			//Updating the animation timer
			this->timer += 100.f * dt;
			if (this->timer >= this->speed)
			{
				//Reseting timer
				this->timer = 0.f;

				//Animating
				if (this->currentRec != this->endRec)
				{
					this->currentRec.left += this->width;
				}
				//If we get in the end of the animation we reset it
				else 
				{	
					this->currentRec.left = this->startRec.left;
				}

				this->sprite.setTextureRect(this->currentRec);
			}
		}

		void reset()
		{
			this->timer = 0.f;
			this->currentRec = this->startRec;
		}
	};
	
	//Variables
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;

public:
	PlayerAnimation(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~PlayerAnimation();

	//Functions
	void addAnimation(
		const std::string key,
		float speed,
		int startFrameX, int startFrameY, 
		int framesX, int framesY, 
		int width, int height
	);
	void play(const std::string key, const float &dt);
};