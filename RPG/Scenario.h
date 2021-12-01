#pragma once

#include "Instance.h"

class Scenario
{
private:
	//Variables
	///Map variables
	sf::RectangleShape shape;
	sf::Texture scenarioTexture;
	std::string key;

	///Objects variables
	sf::RectangleShape* objects;
	int numberObjs;
	sf::Vector2f coordenates;
	sf::Vector2f size;

public:


	//Constructor & Distructor
	Scenario(float x, float y, float witdth, float height, sf::Texture* scenarioTexture, std::string key);
	~Scenario();

	//Functions
	void initObjects();
	sf::RectangleShape* getObjects();
	int getNumObjs();

	void updateCollision(Entity* entity);

	void render(sf::RenderTarget* target);
};
