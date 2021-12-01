#include "GameInstance.h"
#include <iostream>
/*
----------Private Functions----------
*/
void GameInstance::initView()
{
	this->view = new sf::View(sf::Vector2f(500.f, 250.f), sf::Vector2f(1000.f, 500.f));
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

	this->keybinds["MOVE LEFT ARROW"] = this->supportedKeys->at("Left_Arrow");
	this->keybinds["MOVE RIGHT ARROW"] = this->supportedKeys->at("Right_Arrow");
	this->keybinds["MOVE UP ARROW"] = this->supportedKeys->at("Up_Arrow");
	this->keybinds["MOVE DOWN ARROW"] = this->supportedKeys->at("Down_Arrow");

	//this->keybinds["INTERACT"] = this->supportedKeys->at("Z");
	//this->keybinds["CLOSE"] = this->supportedKeys->at("X");

}

void GameInstance::initTextures()
{
	if (!this->textures["PLAYER ANIMATIONS"].loadFromFile("Resources/Images/Sprites/Player/player_temp.png"))
	{
		throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_PLAYER_ANIMATIONS";
	}

	if (!this->textures["CENTRAL MAP TEXTURE"].loadFromFile("Resources/Images/Scenarios/Scenario_test_2.png"))
	{
		throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_SCENARIO_1";
	}

	//if (!this->buttonTexture.loadFromFile("Resources/Images/Buttons/Dialog_buttons.png"))
	//{
		//throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_DIOLOG_IMAGE";
	//}
}

void GameInstance::initPlayers()
{
	this->player = new Player(328.f, 752.f, this->textures["PLAYER ANIMATIONS"]);
	this->invalidMove = false;
}

void GameInstance::initScenarios()
{
	this->scenario["CENTRAL_MAP"] = new Scenario(
		0.f, 0.f,
		400.f, 800.f,
		&this->textures["CENTRAL MAP TEXTURE"],
		"CENTRAL_MAP");

	this->objects = this->scenario["CENTRAL_MAP"]->getObjects();
	//this->npc = this->scenario["CENTRAL_MAP"]->npc;
	//this->npcKey.resize(this->scenario["CENTRAL_MAP"]->numNPCs);
	//this->npcKey = this->scenario["CENTRAL_MAP"]->npcKey;
	//this->interactiveObjects = this->scenario["CENTRAL_MAP"]->interactiveObjects;
	//this->interactiveObjKey.resize(this->scenario["CENTRAL_MAP"]->numberInteractiveObj);
	//this->interactiveObjKey = this->scenario["CENTRAL_MAP"]->interactiveObjKey;

	std::cout << "SCNARIO CREATED";

} // TODO REMOVE LATER ( REDO SCNARIO ENGINE )

//void GameInstance::InitFonts()
//{
//	//if (!this->font.loadFromFile("Resources/Fonts/dpcomic.ttf"))
//	//{
//		//throw("ERROR::PrimaryMenuInstance::COULD NOT LOAD FONT");
//	//}
//}

void GameInstance::initVariables()
{
	//this->objects = nullptr;
	//this->npc = nullptr;
	//this->interactiveObjects = nullptr;
	//this->playerView = nullptr;
	//this->view = nullptr;

}


/*
----------Constructors & Destructors----------
*/

GameInstance::GameInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances)
	: Instance(window, supportedKeys, instances)
{
	this->initVariables();
	this->initKeybinds();
	this->initTextures();
	this->initScenarios();
	this->initPlayers();
	this->initView();
	//this->InitFonts();


}

GameInstance::~GameInstance()
{
	delete this->player;
	delete this->playerView;
	delete this->view;

	//auto it = this->buttons.begin();
	//for (it; it != this->buttons.end(); ++it) // tentar so o it
	//{
	//	delete it->second;
	//}

}


/*
----------Functions----------
*/

//void GameInstance::initializeObjEvent(std::string key)
//{
//
//}

//void GameInstance::initializeDialog(std::string key)
//{
//	if (key == "Old Man")
//	{
//		this->renderButtons(this->window);
//	}
//	if (key == "Little Girl")
//	{
//		std::ifstream ifsgame("Resources/Texts/Little_Girl.ini");
//		if (ifsgame.is_open())
//		{
//			ifsgame >> this->dialogSize;
//			short int count = 0;
//
//			for (short int count = 0; count < this->dialogSize; count++)
//			{
//				std::getline(ifsgame, this->dialogText);
//				this->buttons["Dialog_Little_Girl"] = new Button(
//					0.f,
//					203.f,
//					256.f, 55.f,
//					&this->font, this->dialogText, &this->buttonTexture,
//					sf::Color::Magenta, sf::Color::Blue, sf::Color::Transparent
//				);
//
//				while ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Interact")))))
//				{
//					this->renderButtons(this->window);
//				}
//			}
//		}
//
//		ifsgame.close();
//
//
//	}
//}

void GameInstance::updateView(const float & dt)
{
	this->playerPos = player->getPlayerPos();

	if (this->playerPos.x < 168.f)
	{
		if (this->playerPos.y >= 72.f && this->playerPos.y <= 696.f)
		{
			this->playerView->setCenter(sf::Vector2f(168.f, this->playerPos.y) + (sf::Vector2f(8.f, 16.f)));
		}
		else if (this->playerPos.y < 72.f)
		{
			this->playerView->setCenter(sf::Vector2f(168.f, 72.f) + sf::Vector2f(8.f, 16.f));
		}
		else
		{
			this->playerView->setCenter(sf::Vector2f(168.f, 696.f) + sf::Vector2f(8.f, 16.f));
		}

	}
	else if (this->playerPos.x > 216.f)
	{
		if (this->playerPos.y >= 72.f && this->playerPos.y <= 696.f)
		{
			this->playerView->setCenter(sf::Vector2f(216.f, this->playerPos.y) + sf::Vector2f(8.f, 16.f));
		}
		else if (this->playerPos.y < 72.f)
		{
			this->playerView->setCenter(sf::Vector2f(216.f, 72.f) + sf::Vector2f(8.f, 16.f));
		}
		else
		{
			this->playerView->setCenter(sf::Vector2f(216.f, 696.f) + sf::Vector2f(8.f, 16.f));
		}

	}
	else if (this->playerPos.y < 72.f)
	{
		if (this->playerPos.x >= 168.f && this->playerPos.x <= 216.f)
		{
			this->playerView->setCenter(sf::Vector2f(this->playerPos.x, 72.f) + sf::Vector2f(8.f, 16.f));
		}
		else if (this->playerPos.x < 168.f)
		{
			this->playerView->setCenter(sf::Vector2f(168.f, 72.f) + sf::Vector2f(8.f, 16.f));
		}
		else
		{
			this->playerView->setCenter(sf::Vector2f(216.f, 72.f) + sf::Vector2f(8.f, 16.f));
		}

	}
	else if (this->playerPos.y > 696.f)
	{
		if (this->playerPos.x >= 168.f && this->playerPos.x <= 216.f)
		{
			this->playerView->setCenter(sf::Vector2f(this->playerPos.x, 696.f) + sf::Vector2f(8.f, 16.f));
		}
		else if (playerPos.x < 168.f)
		{
			this->playerView->setCenter(sf::Vector2f(168.f, 696.f) + sf::Vector2f(8.f, 16.f));
		}
		else
		{
			this->playerView->setCenter(sf::Vector2f(216.f, 696.f) + sf::Vector2f(8.f, 16.f));
		}
	}

	else
	{
		this->playerView->setCenter(sf::Vector2f(playerPos.x, playerPos.y) + sf::Vector2f(8.f, 16.f));
	}

}

void GameInstance::updateInput(const float & dt)
{
	this->topRightCord = this->player->getTopRightCord();
	this->topLeftCord = this->player->getTopLeftCord();
	this->bottomRightCord = this->player->getBottomRightCord();
	this->bottomLeftCord = this->player->getBottomLeftCord();

	std::cout << "\n" << "top RightCord = " << this->topRightCord.x <<
		", " << this->topRightCord.y << "\n";

	std::cout << "\n" << "top LeftCord = " << this->topLeftCord.x <<
		", " << this->topLeftCord.y << "\n";

	std::cout << "\n" << "bottom RightCord = " << this->bottomRightCord.x <<
		", " << this->bottomRightCord.y << "\n";

	std::cout << "\n" << "bottom LeftCord = " << this->bottomLeftCord.x <<
		", " << this->bottomLeftCord.y << "\n";

	//Closing the game ( for now )s
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Exit"))))
	{
		this->playerView = new sf::View(sf::Vector2f(500.f, 250.f), sf::Vector2f(1000.f, 500.f)); // Default values do better later
		this->window->setView(*this->playerView);
		this->endInstance();

	}

	//Player Input
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Interact"))))
	{
		for (int i = 0; i < this->scenario["CENTRAL_MAP"]->numberInteractiveObj; i++)
		{
			if (((this->player->topLeftCord.x >= this->interactiveObjects[i].getPosition().x) &&
				(this->player->topLeftCord.y >= this->interactiveObjects[i].getPosition().y)) &&
				((this->player->topLeftCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
				(this->player->topLeftCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
			{
				this->initializeObjEvent(this->interactiveObjKey[i]);
			}
			else
				if ( ((this->player->topRightCord.x >= this->interactiveObjects[i].getPosition().x) &&
					(this->player->topRightCord.y >= this->interactiveObjects[i].getPosition().y)) &&
					((this->player->topRightCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
					(this->player->topRightCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
				{
					this->initializeObjEvent(this->interactiveObjKey[i]);
				}
			else
				if (((this->player->bottomLeftCord.x >= this->interactiveObjects[i].getPosition().x) &&
					(this->player->bottomLeftCord.y >= this->interactiveObjects[i].getPosition().y)) &&
					((this->player->bottomLeftCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
					(this->player->bottomLeftCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
				{
					this->initializeObjEvent(this->interactiveObjKey[i]);
				}
			else
				if (((this->player->bottomRightCord.x >= this->interactiveObjects[i].getPosition().x) &&
					(this->player->bottomRightCord.y >= this->interactiveObjects[i].getPosition().y)) &&
					((this->player->bottomRightCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
					(this->player->bottomRightCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
				{
					this->initializeObjEvent(this->interactiveObjKey[i]);
				}
		}

		for (int i = 0; i < this->scenario["CENTRAL_MAP"]->numNPCs; i++)
		{
			if ( ((this->player->topLeftCord.x >= this->npc[i].getPosition().x) &&
				(this->player->topLeftCord.y >= this->npc[i].getPosition().y)) &&
				((this->player->topLeftCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
				(this->player->topLeftCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y) )
			{
				this->initializeDialog(this->npcKey[i]);
			}
			else
				if ( ((this->player->topRightCord.x >= this->npc[i].getPosition().x) &&
					(this->player->topRightCord.y >= this->npc[i].getPosition().y)) &&
					((this->player->topRightCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
					(this->player->topRightCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y) )
				{

					this->initializeDialog(this->npcKey[i]);
				}
			else
				if ( ((this->player->bottomLeftCord.x >= this->npc[i].getPosition().x) &&
					(this->player->bottomLeftCord.y >= this->npc[i].getPosition().y)) &&
					((this->player->bottomLeftCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
					(this->player->bottomLeftCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y) )
				{
					this->initializeDialog(this->npcKey[i]);
				}
			else
				if ( ((this->player->bottomRightCord.x >= this->npc[i].getPosition().x) &&
					(this->player->bottomRightCord.y >= this->npc[i].getPosition().y)) &&
					((this->player->bottomRightCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
					(this->player->bottomRightCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y) )
				{
					this->initializeDialog(this->npcKey[i]);
				}
		}
	}*/

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE LEFT")))) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE LEFT ARROW")))))
	{
		//TODO The colission will only work for sprites larger than the player, need one more check foir that ( doesnt matter rn )
		for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumObjs(); i++)
		{
			if (((this->topLeftCord.x - 3.5f) <= this->objects[i].getPosition().x + this->objects[i].getGlobalBounds().width) &&
				(this->topLeftCord.x >= (this->objects[i].getPosition().x + this->objects[i].getGlobalBounds().width - 3.5f)))
			{
				if (
					(
					(this->topRightCord.y >= this->objects[i].getPosition().y) &&
						(this->topRightCord.y <= (this->objects[i].getPosition().y +
							this->objects[i].getGlobalBounds().height))
						)
					||
					(
					(this->bottomRightCord.y >= this->objects[i].getPosition().y) &&
						(this->bottomRightCord.y <= (this->objects[i].getPosition().y +
							this->objects[i].getGlobalBounds().height))
						)
					)
				{
					std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
						" ," << this->objects[i].getPosition().y << " I Stoped the movement";

					this->player->FinishMovement();
					return;
				}
			}
		}
		this->player->move(-1.f, 0.f, dt);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE RIGHT")))) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE RIGHT ARROW")))))
	{

		//TODO The colission will only work for sprites larger than the player, need one more check foir that ( doesnt matter rn )
		for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumObjs(); i++)
		{
			if (((this->topRightCord.x + 3.f) >= this->objects[i].getPosition().x) &&
				(this->topRightCord.x <= (this->objects[i].getPosition().x + 3.f)))
			{
				if (
					(
					(this->topRightCord.y >= this->objects[i].getPosition().y) &&
						(this->topRightCord.y <= (this->objects[i].getPosition().y +
							this->objects[i].getGlobalBounds().height))
						)
					||
					(
					(this->bottomRightCord.y >= this->objects[i].getPosition().y) &&
						(this->bottomRightCord.y <= (this->objects[i].getPosition().y +
							this->objects[i].getGlobalBounds().height))
						)
					)
				{
					std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
						" ," << this->objects[i].getPosition().y << " I Stoped the movement";

					this->player->FinishMovement();
					return;
				}
			}
		}
		this->player->move(1.f, 0.f, dt);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE UP")))) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE UP ARROW")))))
	{
		//TODO The colission will only work for sprites larger than the player, need one more check foir that ( doesnt matter rn )
		for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumObjs(); i++)
		{
			if (((this->topRightCord.y - 1.5f) <=
				this->objects[i].getPosition().y + this->objects[i].getGlobalBounds().height) &&
				(this->topRightCord.y >= (this->objects[i].getPosition().y + this->objects[i].getGlobalBounds().height - 1.5f)))
			{
				if (
					(
					(this->topLeftCord.x >= this->objects[i].getPosition().x) &&
						(this->topLeftCord.x <= (this->objects[i].getPosition().x +
							this->objects[i].getGlobalBounds().width))
						)
					||
					(
					(this->topRightCord.x >= this->objects[i].getPosition().x) &&
						(this->topRightCord.x <= (this->objects[i].getPosition().x +
							this->objects[i].getGlobalBounds().width))
						)
					)
				{
					std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
						" ," << this->objects[i].getPosition().y << " I Stoped the movement";

					this->player->FinishMovement();
					return;
				}
			}
		}
		this->player->move(0.f, -1.f, dt);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE DOWN")))) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE DOWN ARROW")))))
	{
		//TODO The colission will only work for sprites larger than the player, need one more check foir that ( doesnt matter rn )
		for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumObjs(); i++)
		{
			if (((this->bottomLeftCord.y + 1.5f) >=
				this->objects[i].getPosition().y) &&
				(this->bottomLeftCord.y <= (this->objects[i].getPosition().y + 1.5f)))
			{
				if (
					(
					(this->bottomLeftCord.x >= this->objects[i].getPosition().x) &&
						(this->bottomLeftCord.x <= (this->objects[i].getPosition().x +
							this->objects[i].getGlobalBounds().width))
						)
					||
					(
					(this->bottomRightCord.x >= this->objects[i].getPosition().x) &&
						(this->bottomRightCord.x <= (this->objects[i].getPosition().x +
							this->objects[i].getGlobalBounds().width))
						)
					)
				{
					std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
						" ," << this->objects[i].getPosition().y << " I Stoped the movement";

					this->player->FinishMovement();
					return;
				}
			}
		}
		this->player->move(0.f, 1.f, dt);
	}
}

//void GameInstance::updateButtons()
//{
//	for (auto &it : this->buttons)
//	{
//		it.second->update(this->mousePositionView);
//	}
//
//}

void GameInstance::update(const float& dt)
{
	this->updateMousePositions(); // TO DO (playerview_
	this->updateInput(dt);
	this->player->update(dt);
	this->scenario["CENTRAL_MAP"]->updateCollision(this->player);
	this->updateView(dt);

}

//void GameInstance::renderButtons(sf::RenderTarget * target)
//{
//	for (auto &it : this->buttons)
//	{
//		it.second->render(target);
//	}
//}

void GameInstance::render(sf::RenderTarget* target)
{
	if (!target) // if target is nullpr
	{
		target = this->window;
	}
	//(DEBUG)


	this->scenario["CENTRAL_MAP"]->render(target);
	this->player->render(*target);
	this->window->setView(*playerView);

}