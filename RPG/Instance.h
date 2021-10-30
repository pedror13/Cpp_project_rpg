#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>



#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
//#include "SFML/Network.hpp"

class Instance
{
  private:
	  //Variables
	  sf::RenderWindow* window;
	  std::vector<sf::Texture> textures;
	  // do Sprites, players 

  public:
	  //Constructors & Destructors
	  Instance(sf::RenderWindow* window);
	  virtual ~Instance();

	  //Functions
	  ////Pure Virtual for  inheritance
	  virtual void endInstance() = 0; // Make sure when we want to end a instance
	  virtual void update(const float& dt) = 0; 
	  virtual void render(sf::RenderTarget* target = nullptr) = 0; //With target i can render to some specific stuff
};

