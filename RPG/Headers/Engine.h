#pragma once

#include "../Headers/PrimaryMenuInstance.h"

class Engine
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
	sf::Clock dtClock;

	///Delta time
	float dt;
	
	///Will manage the game's instances
	std::stack<Instance*> instances;

	///Will keep the supported keys for each instances
	std::map<std::string, int> supportedKeys;

	//Initializer Functions
	void initVariables();
	void initWindow();
	void initKeys();
	void initInstance();

public:
	//Constructors & Destructors
	Engine();
	virtual ~Engine();

	//Functions
	void endApplication();

	///Update functions
	void updateDt();
	void updateSFMLEvents();
	void update();

	///Render funtions
	void render();

	///Core
	void run();
};