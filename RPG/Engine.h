#pragma once

#include "GameInstance.h"

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

	  //Initializer Functions
	  void initWindow();
	  void initInstance();

  public:
	  //Constructors & Destructors
	  Engine();
	  virtual ~Engine();


	  //Functions
	  void updateDt();
	  void updateSFMLEvents();
	  void update();
	  void render();
	  void run();
};

