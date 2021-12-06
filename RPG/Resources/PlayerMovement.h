#pragma once

#include <ctime>
#include <cstdlib>
#include <fstream>
#include<iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class PlayerMovement
{
private:
	//Variables
	sf::Sprite& sprite;
	sf::Vector2f speed;

	float maxSpeed;
	float acceleration;
	float deceleration;


public:

	//Constructors & Destructors
	PlayerMovement(sf::Sprite& sprite, float maxSpeed, float acceleration, float deceleration);
	virtual ~PlayerMovement();

	//Functions
	const sf::Vector2f& getVelocity() const;

	const short int getDirectionCharMov() const;
	void FinishMovement();
	void update(const float& dt);
	void move(const float diretionX, const float directionY, const float& dt);
};