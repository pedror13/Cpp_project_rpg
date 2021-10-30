#include "Engine.h"

/*
----------Static Functions----------
*/



/*
----------Initializer Functions----------
*/

void Engine::initWindow()
{
	/*Creates a SFML using window.ini file.*/

	//Values by default
	std::string title = "None";
	sf::VideoMode WindowSize(800, 600);
	unsigned framerateMax = 120;
	bool verticalSyncEnable = false;

	std::ifstream ifs("Config/window.ini");
	if(ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> WindowSize.width >> WindowSize.height;
		ifs >> framerateMax;
		ifs >> verticalSyncEnable;
	}

	ifs.close();

	this->window = new sf::RenderWindow(WindowSize, title);
	this->window->setFramerateLimit(framerateMax);
	this->window->setVerticalSyncEnabled(verticalSyncEnable);
}

void Engine::initInstance()
{
	/*Creates a new instance in the program*/

	this->instances.push(new GameInstance(this->window));
}

/*
----------Constructors & Destructors----------
*/
Engine::Engine()
{
	this->initWindow();
	this->initInstance();
}

Engine::~Engine()
{
	delete this->window;

	while (this->instances.empty())
	{
		delete this->instances.top(); //Deleting the data
		this->instances.pop();  //Deleting the points
	}
}

/*
----------Functions----------
*/

void Engine::updateDt()
{
	/*Used for mantain track of how much time takes to update
	and render one frame.*/

	this->dt = this->dtClock.restart().asSeconds();
	system("cls");
	std::cout << "Frame rate : "<< this->dt << "\n";
}

void Engine::updateSFMLEvents()
{
	/*Interact with the events pulled by the system
	  (maybe will be another to user events. */

	while (this->window->pollEvent(this->sfmlEvent))
	{
		if (this->sfmlEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Engine::update()
{
	this->updateSFMLEvents();

	if (!this->instances.empty())
	{
		this->instances.top()->update(this->dt);
	}

}

void Engine::render()
{
	window->clear();

	//Render Itens
	if (!this->instances.empty())
	{
		this->instances.top()->render(); //this->window 
	}
	this->window->display();
}

void Engine::run()
{
	while(this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
