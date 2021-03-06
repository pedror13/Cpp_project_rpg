#pragma once

#include "../Headers/Instance.h"

class Scenario
{
private:
	//Variables
	///Map variables
	sf::RectangleShape shape;
	sf::Texture scenarioTexture;
	std::string key;

	///Map's objects variables
	sf::Vector2f coordenates;
	sf::Vector2f size;

	sf::RectangleShape* objects;
	int numberObjs;

	sf::RectangleShape* npc;
	std::vector<short int> dialogSize;
	int numberNPCs;

	sf::RectangleShape* interactiveObjects;
	std::vector<short int> interactiveObjSize;
	int numberInteractiveObj;

public:

	//Constructor & Distructor
	Scenario(float x, float y, float witdth, float height, sf::Texture* scenarioTexture, std::string key);
	~Scenario();

	//Functions
	void initObjects();

	///Access functions
	sf::RectangleShape* getObjects();
	sf::RectangleShape* getNPCs();
	sf::RectangleShape* getInteractiveObj();
	int getNumObjs();
	int getNumNPC();
	int getNumInteractObj();
	std::vector<short int>& GetSizeDialog();
	std::vector<short int>& GetKeyInteractiveObj();

	///Update functions
	void updateCollision(Entity* entity);

	///Render functions
	void render(sf::RenderTarget* target);
};
