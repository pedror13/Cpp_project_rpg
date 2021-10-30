#include "GameInstance.h"

/*
----------Constructors & Destructors----------
*/

GameInstance::GameInstance(sf::RenderWindow* window) // Olhar por que caralhos isso funciona
	:Instance(window)
{

}

GameInstance::~GameInstance()
{

}

/*
----------Functions----------
*/

void GameInstance::endInstance()
{

}

void GameInstance::update(const float& dt)
{
	std::cout << "GameInstance is working Boy!" << "\n";
}

void GameInstance::render(sf::RenderTarget* target)
{

}


