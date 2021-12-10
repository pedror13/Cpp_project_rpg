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
	unsigned framerateMax = 120;
	bool verticalSyncEnable = false;

	std::ifstream ifs("Config/Engine/window.ini");
	if (ifs.is_open())
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
	/*
		Inicialize the buttons that will be used in all instances, their functions will be define in each instance
	*/

	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"] = sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S;

	this->supportedKeys["Left_Arrow"] = sf::Keyboard::Key::Left;
	this->supportedKeys["Right_Arrow"] = sf::Keyboard::Key::Right;
	this->supportedKeys["Up_Arrow"] = sf::Keyboard::Key::Up;
	this->supportedKeys["Down_Arrow"] = sf::Keyboard::Key::Down;

	this->supportedKeys["Z"] = sf::Keyboard::Key::Z;
	this->supportedKeys["X"] = sf::Keyboard::Key::X;
	this->supportedKeys["Space"] = sf::Keyboard::Key::Space;
}

void Engine::initInstance()
{
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
		delete this->instances.top();
		this->instances.pop();
	}
}

/*
----------Functions----------
*/

void Engine::endApplication()
{

}

void Engine::updateDt()
{
	/*
	Used for mantain track of how much time takes to update
	and render one frame, i.e game's frame rate
	*/

	this->dt = this->dtClock.restart().asSeconds();

}

void Engine::updateSFMLEvents()
{
	/*
	Interact with the events pulled by the system
	*/

	while (this->window->pollEvent(this->sfmlEvent))
	{
		if (this->sfmlEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Engine::update()
{
	/*
		General update for this instances that checks if the game will keep running
	*/
	this->updateSFMLEvents();

	if (!this->instances.empty())
	{
		this->instances.top()->update(this->dt);

		if (this->instances.top()->getFinish()) // Deleting that given instance
		{
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

	if (!this->instances.empty())
	{
		this->instances.top()->render();
	}
	this->window->display();
}

void Engine::run()
{
	/*
		The loop where the whole game will occurs	
	*/
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}