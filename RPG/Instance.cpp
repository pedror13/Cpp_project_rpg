#include "Instance.h"


/*
----------Constructors & Destructors----------
*/
Instance::Instance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->instances = instances;
	this->finish = false;
}

Instance::~Instance()
{

}

/*
----------Functions----------
*/

const bool & Instance::getFinish() const
{	
	/*Aux checkFinish()*/

	return this->finish;
}

void Instance::endInstance()
{
	this->finish = true;
}

void Instance::updateMousePositions()
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}
