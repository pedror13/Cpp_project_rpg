#pragma once

#include "PrimaryMenuInstance.h"

//Class that will work as the game engine
class Engine
{
  private:
      //Variables
	  sf::RenderWindow* window;
	  sf::Event sfmlEvent;
	  sf::Clock dtClock;

	  float dt; //Delta Time

	  std::stack<Instance*> instances; // Will manage the instances

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

	  ///Update
	  void updateDt();
	  void updateSFMLEvents();
	  void update();

	  ///Render
	  void render();

	  ///Core
	  void run();
};

