#include "Engine.h"

/*
----------Functions----------
*/



/*
----------Initializer Functions----------
*/

void Engine::initVariables()
{ 
	this->window = nullptr;
	this->dt = 0.f;
}

void Engine::initWindow()
{
	/*Creates a SFML using window.ini file.*/

	//Values by default
	std::string title = "None";
	sf::VideoMode WindowSize(600, 300);
	sf::VideoMode::getFullscreenModes;
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

void Engine::initKeys()
{
	/*Inicialize the buttons that will be used in all instances, their functions will be define in each instance*/

	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"]= sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S;

}

void Engine::initInstance()
{
	/*Creates a new instance in the program*/

	this->instances.push(new PrimaryMenuInstance(this->window, &this->supportedKeys, &this->instances));
}

/*
----------Constructors & Destructors----------
*/
Engine::Engine()
{
	this->initWindow();
	this->initKeys();
	this->initInstance();
}

Engine::~Engine()
{
	delete this->window;

	while (!this->instances.empty())
	{
		delete this->instances.top(); //Deleting the data
		this->instances.pop();  //Deleting the points
	}
}

/*
----------Functions----------
*/

void Engine::endApplication()
{
	//std::cout << "Ending application!" << "\n";
}

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
	
		if (this->instances.top()->getFinish()) // Deleting that given instance
		{
			/*Later save instances info before ereasing it
			i.e caracters new info, exp,options clicked etc*/
			this->instances.top()->endInstance();
			delete this->instances.top();
			this->instances.pop();
		}
	}
	else
	{
		//Aplication end
		this->endApplication();
		this->window->close();
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
