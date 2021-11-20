#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class Scenario
{
   private:
	   std::map<std::string, sf::Texture> scenarioTexture;

   public:

	   //Constructor & Distructor
	   Scenario();
	   ~Scenario();

};

