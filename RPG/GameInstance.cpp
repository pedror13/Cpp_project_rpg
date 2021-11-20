#include "GameInstance.h"

/*
----------Private Functions----------
*/
void GameInstance::initView()
{
	this->playerPos = player->getPlayerPos() + sf::Vector2f(8.f, 16.f);
	this->playerView = new sf::View(playerPos, sf::Vector2f(352.f, 176.f));
}

void GameInstance::initKeybinds()
{
	//Maybe later do ifs of existence of the commands
	this->keybinds["Exit"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE DOWN"] = this->supportedKeys->at("S");

}

void GameInstance::initTextures()
{
	if (!this->textures["PLAYER ANIMATIONS"].loadFromFile("Resources/Images/Sprites/Player/player_temp.png"))
	{
		throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_PLAYER_ANIMATIONS";
	}

}

void GameInstance::initPlayers()
{
	this->player = new Player(168.f, 461.f, this->textures["PLAYER ANIMATIONS"]);
}

void GameInstance::initScenarios()
{
	this->scenario.setOrigin(sf::Vector2f(0.f, 0.f));

	if (!this->scenarioTexture.loadFromFile("Resources/Images/Scenarios/Scenario_test_2.png"))
	{
		throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_SCENARIO_1"; // JOGAR PARA INITVARIABLES
	}
	this->scenario.setTexture(this->scenarioTexture);
} // TODO REMOVE LATER ( REDO SCNARIO ENGINE )

/*
----------Constructors & Destructors----------
*/

GameInstance::GameInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances)
	: Instance(window, supportedKeys, instances)
{
	this->initKeybinds();
	this->initTextures();
	this->initScenarios();
	this->initPlayers();
	this->initView();

}

GameInstance::~GameInstance()
{
	delete this->player;
	delete this->playerView;
}

/*
----------Functions----------
*/
void GameInstance::updateView(const float & dt)
{
	this->playerPos = player->getPlayerPos();
	this->playerView->setCenter(playerPos + sf::Vector2f(8.f, 16.f));
}

void GameInstance::updateInput(const float & dt)
{
	//Closing the game ( for now )s
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Exit"))))
	{
		//std::cout << " THE APLICATION WAS CLOSED"; // TO DO REMOVE LATER ( DEBUG )
		this->endInstance();
		
	}

	//Player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE LEFT"))))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE RIGHT"))))
	{
		this->player->move(1.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE UP"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}

	//Future checking for keys and stuff
}

void GameInstance::update(const float& dt)
{
	this->updateMousePositions(); // TO DO (playerview_
	this->updateInput(dt/10); // TODO CHECK LATER THE CONSEQUENCES
	this->player->update(dt);
	this->updateView(dt);

//	system("cls");
//std::cout << "x: " << this->mousePositionView.x 
//		  << ", y = " << this->mousePositionView.y << std::endl; // TODO REMOVE LATER ( DEBUG )

}

void GameInstance::render(sf::RenderTarget* target)
{
	if (!target) // if target is nullpr
	{
		target = this->window;
	}

	target->draw(this->scenario);
	this->player->render(target);
	this->window->setView(*playerView);
	
}


