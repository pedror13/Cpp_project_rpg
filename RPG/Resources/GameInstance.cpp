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

	this->keybinds["INTERACT"] = this->supportedKeys->at("Z");
	this->keybinds["CLOSE"] = this->supportedKeys->at("X");

	this->keybinds["START COMBAT"] = this->supportedKeys->at("Space");

}

void GameInstance::initTextures()
{
	if (!this->textures["PLAYER ANIMATIONS"].loadFromFile("Resources/Images/Sprites/Player/Main_Character_RED.png"))
	{
		throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_PLAYER_ANIMATIONS";
	}

	if (!this->textures["CENTRAL MAP TEXTURE"].loadFromFile("Resources/Images/Scenarios/Scenario_01.png"))
	{
		throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_SCENARIO_1";
	}

	if (!this->buttonTexture.loadFromFile("Resources/Images/Buttons/Dialog_buttons.png"))
	{
		throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_DIOLOG_TEXTURE_IMAGE";
	}
}

void GameInstance::initPlayers()
{
	this->player = new Player(328.f, 752.f, this->textures["PLAYER ANIMATIONS"]);

	this-> playerLevel = 1;
	this->playerAtk = 5.f;
	this->playerDef = 0.f;
	this->playerHP = { 100.f, 100.f };
	this->playerMP = { 40.f, 40.f };

	this->playerSkills.resize(3);
	this->playerSkills[0].first = 1.f;
	this->playerSkills[0].second = 0.f;
	this->playerSkills[1].first = 1.2f;
	this->playerSkills[1].second = 10.f;
	this->playerSkills[2].first = 1.8f;
	this->playerSkills[2].second = 15.f;

}

void GameInstance::initScenarios()
{
	this->scenario["CENTRAL_MAP"] = new Scenario(
		0.f, 0.f,
		400.f, 800.f,
		&this->textures["CENTRAL MAP TEXTURE"],
		"CENTRAL_MAP");

	this->objects = this->scenario["CENTRAL_MAP"]->getObjects();
	this->npc = this->scenario["CENTRAL_MAP"]->getNPCs();
	this->dialogSize.resize(this->scenario["CENTRAL_MAP"]->getNumNPC());
	this->dialogSize = this->scenario["CENTRAL_MAP"]->GetSizeDialog();
	this->interactiveObjects = this->scenario["CENTRAL_MAP"]->getInteractiveObj();
	this->InteractionsSize.resize(this->scenario["CENTRAL_MAP"]->getNumInteractObj());
	this->InteractionsSize = this->scenario["CENTRAL_MAP"]->GetKeyInteractiveObj();

	if (!this->scenario["CENTRAL_MAP"])
	{
		throw("ERROR::GameInstance::FAILED_TO_CREAT_CENTRAL_MAP_SCENARIO");
	}

}

void GameInstance::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/dpcomic.ttf"))
	{
		throw("ERROR::GameInstance::FAILED_TO_LOAD_DIALOG_FONT");
	}
	if (!this->font1.loadFromFile("Resources/Fonts/PTSansNarrow-Regular.ttf"))
	{
		throw("ERROR::GameInstance::FAILED_TO_LOAD_COMBAT_WINDOWS_FONT1");
	}
	if (!this->font2.loadFromFile("Resources/Fonts/kenta.otf"))
	{
		throw("ERROR::GameInstance::FAILED_TO_LOAD_COMBAT_WINDOWS_FONT2");
	}

}

void GameInstance::initButtons()
{
	std::ifstream girl0("Config/Scenarios/Scenario_0/Texts/Little_Girl_0.ini");
	if (girl0.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(girl0, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_LITTLE_GIRL_DIALOG_0";
		}

		this->buttons["Dialog_Little_Girl_0"] = new Button(
			0.f, 50.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		girl0.close();
	}

	std::ifstream girl1("Config/Scenarios/Scenario_0/Texts/Little_Girl_1.ini");
	if (girl1.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(girl1, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_LITTLE_GIRL_DIALOG_1";
		}

		this->buttons["Dialog_Little_Girl_1"] = new Button(
			0.f, 50.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		girl1.close();
	}

	std::ifstream girl2("Config/Scenarios/Scenario_0/Texts/Little_Girl_2.ini");
	if (girl2.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(girl2, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_LITTLE_GIRL_DIALOG_2";
		}

		this->buttons["Dialog_Little_Girl_2"] = new Button(
			0.f, 50.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		girl2.close();
	}

	std::ifstream girl3("Config/Scenarios/Scenario_0/Texts/Little_Girl_3.ini");
	if (girl3.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(girl3, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_LITTLE_GIRL_DIALOG_3";
		}

		this->buttons["Dialog_Little_Girl_3"] = new Button(
			0.f, 50.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::Magenta, sf::Color::White, sf::Color::Transparent
		);

		girl3.close();
	}

	std::ifstream oldMan0("Config/Scenarios/Scenario_0/Texts/Old_Man_0.ini");
	if (oldMan0.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(oldMan0, dialogText);
		if (dialogText == "NONE")
		{
		
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_OLD_MAN_DIALOG_0";
		}

		this->buttons["Dialog_Old_Man_0"] = new Button(
			0.f, 530.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		oldMan0.close();
	}

	std::ifstream oldMan1("Config/Scenarios/Scenario_0/Texts/Old_Man_1.ini");
	if (oldMan1.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(oldMan1, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_OLD_MAN_DIALOG_1";
		}

		this->buttons["Dialog_Old_Man_1"] = new Button(
			0.f, 530.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		oldMan1.close();
	}

	std::ifstream oldMan2("Config/Scenarios/Scenario_0/Texts/Old_Man_2.ini");
	if (oldMan2.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(oldMan2, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_OLD_MAN_DIALOG_2";
		}

		this->buttons["Dialog_Old_Man_2"] = new Button(
			0.f, 530.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		oldMan2.close();
	}

	std::ifstream Door0("Config/Scenarios/Scenario_0/Texts/Door_0.ini");
	if (Door0.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(Door0, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_DOOR_0";
		}

		this->buttons["Door_Interaction_0"] = new Button(
			50.f, 520.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		Door0.close();
	}

	std::ifstream Portal0("Config/Scenarios/Scenario_0/Texts/Portal_0.ini");
	if (Portal0.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(Portal0, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_PORTAL_0";
		}

		this->buttons["Portal_Interaction_0"] = new Button(
			55.f, 25.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);

		Portal0.close();
	}

	std::ifstream Portal1("Config/Scenarios/Scenario_0/Texts/Portal_1.ini");
	if (Portal1.is_open())
	{
		std::string dialogText = "NONE";
		std::getline(Portal1, dialogText);
		if (dialogText == "NONE")
		{
			throw "ERROR::GAME_INSTANCE::COULD_NOT_LOAD_PORTAL_1";
		}

		this->buttons["Portal_Interaction_1"] = new Button(
			55.f, 25.f, // 203
			256.f, 45.f,
			&this->font, dialogText, 11,
			&this->buttonTexture,
			sf::Color::White, sf::Color::White, sf::Color::Transparent
		);
		Portal1.close();
	}

	sf::Texture* defaultTexture = nullptr;

	this->buttons["Attack"] = new Button(
		228.f, 82.f, // 203
		71.f, 35.f,
		&this->font2, "Attack", 12,
		defaultTexture,
		sf::Color::White, sf::Color::Blue, sf::Color::Transparent
	);

	this->buttons["Skill_1"] = new Button(
		308.f, 82.f, // 203
		71.f, 35.f,
		&this->font2, "Fire Ball", 12,
		defaultTexture,
		sf::Color::White, sf::Color::Blue, sf::Color::Transparent
	);
	this->buttons["Skill_2"] = new Button(
		306.f, 121.f, // 203
		71.f, 35.f,
		&this->font2, "Thunder", 12,
		defaultTexture,
		sf::Color::White, sf::Color::Blue, sf::Color::Transparent
	);

	this->buttons["Run"] = new Button(
		227.f, 121.f, // 203
		71.f, 35.f,
		&this->font2, "Run", 12,
		defaultTexture,
		sf::Color::White, sf::Color::Blue, sf::Color::Transparent
	);

}

void GameInstance::initCombatWindows()
{
	this->combatDisplay.setFillColor(sf::Color::Black);
	this->combatDisplay.setOutlineThickness(1.f);
	this->combatDisplay.setOutlineColor(sf::Color::Cyan);
	this->combatDisplay.setPosition(sf::Vector2f(233.f, 25.f));
	this->combatDisplay.setSize(sf::Vector2f(150.f, 55.f));

	this->actionsMenu.setFillColor(sf::Color::Black);
	this->actionsMenu.setOutlineThickness(1.f);
	this->actionsMenu.setOutlineColor(sf::Color::Cyan);
	this->actionsMenu.setPosition(sf::Vector2f(233.f, 83.f));
	this->actionsMenu.setSize(sf::Vector2f(150.f, 92.f));
}

void GameInstance::initVariables()
{
	this->playerView = nullptr;
	this->view = nullptr;
	this->objects = nullptr;
	this->npc = nullptr;
	this->interactiveObjects = nullptr;
	this->playerOnInteraction = false;
	this->playerOnCombat = false;
	this->interactionDelay = false;
	this->dialogCount = 0;
	this->interactionTimer = 2.f;
	this->playerLevel = 0;
	this->playerAtk = 0.f;
	this->playerDef = 0.f;
	std::pair<float, float> playerHP = { 0.f, 0.f };
	std::pair<float, float> playerMP = { 0.f, 0.f };
	this->combatCount = 0;
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
	this->InitFonts();
	this->initButtons();
	this->initCombatWindows();

}

GameInstance::~GameInstance()
{
	delete this->player;
	delete this->playerView;
	delete this->view;
	delete[] this->npc;
	delete[] this->objects;
	delete[] this->interactiveObjects;

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	for (auto it = this->scenario.begin(); it != this->scenario.end(); ++it)
	{
		delete it->second;
	}
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		delete it->second;
	}
}


/*
----------Functions----------
*/

void GameInstance::enemyTurn()
{
	if (this->enemies["Goblin"]->mp.first >= this->enemies["Goblin"]->skills[1].second)
	{
		this->enemies["Goblin"]->mp.first -= this->enemies["Goblin"]->skills[1].second;
		this->playerHP.first -= ( (this->enemies["Goblin"]->atk * this->enemies["Goblin"]->skills[1].first) - this->playerDef);
		return;
	}
	this->playerHP.first -= ((this->enemies["Goblin"]->atk * this->enemies["Goblin"]->skills[0].first) - this->playerDef);
	return;
}

void GameInstance::levelUP()
{
	this->playerLevel++;

	this->playerHP.second *= (1.f + static_cast<float>(this->playerLevel) / 100);
	this->playerHP.first = this->playerHP.second;

	this->playerMP.second *= (1.f + static_cast<float>(this->playerLevel) / 8);
	this->playerMP.first = this->playerMP.second;

	this->playerAtk *= (1.f + static_cast<float>(this->playerLevel) / 50);
	this->playerDef *= (1.f + static_cast<float>(this->playerLevel) / 20);

	this->playerSkills[2].first *= (1.1f);

}

void GameInstance::initializeCombat()
{
	this->playerOnCombat = true;
	this->enemies["Goblin"] = new Enemies("Goblin", this->playerLevel);
}

void GameInstance::initializeDialog(short int key)
{
	// NPC - 0 = Old man, down part map 
	// NPC - 1 = Little girl, upper part map

	this->playerOnInteraction = true;

	if (key == 0)
	{
		if (this->dialogCount == 0)
		{
			this->atualDialog = "Dialog_Old_Man_0";
			this->dialogCount++;
			return;
		}
		else
			if (this->dialogCount == 1)
			{
				this->atualDialog = "Dialog_Old_Man_1";
				this->dialogCount++;
				return;
			}
			else
				if (this->dialogCount == 2)
				{
					this->atualDialog = "Dialog_Old_Man_2";
					this->dialogCount++;
					return;
				}
	}
	if (key == 1)
	{	

		if (this->dialogCount == 0)
		{
			this->atualDialog = "Dialog_Little_Girl_0";
			this->dialogCount++;
			return;
		}
		else
			if (this->dialogCount == 1)
			{
				this->atualDialog = "Dialog_Little_Girl_1";
				this->dialogCount++;
				return;
			}
			else
				if (this->dialogCount == 2)
				{
					this->atualDialog = "Dialog_Little_Girl_2";
					this->dialogCount++;
					return;
				}
				else
					if (this->dialogCount == 3)
					{
						this->atualDialog = "Dialog_Little_Girl_3";
						this->dialogCount++;
						return;
					}

	}
}

void GameInstance::initializeInteraction(short int key)
{
	// InteractiveObj - 0 = Portal, map's upper-right part
	// InteractiveObj - 1 = Door, map's lower-right part

	this->playerOnInteraction = true;

	if (key == 0)
	{
		if (this->dialogCount == 0)
		{
			this->atualDialog = "Portal_Interaction_0";
			this->dialogCount++;
			return;
		}
		else
			if (this->dialogCount == 1)
			{
				this->atualDialog = "Portal_Interaction_1";
				this->dialogCount++;
				return;
			}
	}
	if (key == 1)
	{

		if (this->dialogCount == 0)
		{
			this->atualDialog = "Door_Interaction_0";
			this->dialogCount++;
			return;
		}
		
	}
}

void GameInstance::updateView(const float & dt)
{
	this->playerPos = player->getPlayerPos();

	if (this->playerPos.x < 168.f)
	{
		if (this->playerPos.y >= 72.f && this->playerPos.y <= 696.f)
		{
			this->playerView->setCenter(sf::Vector2f(168.f, std::floor(this->playerPos.y)) + (sf::Vector2f(8.f, 16.f)));
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
			this->playerView->setCenter(sf::Vector2f(216.f, std::floor(this->playerPos.y)) + sf::Vector2f(8.f, 16.f));
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
			this->playerView->setCenter(sf::Vector2f(std::floor(this->playerPos.x), 72.f) + sf::Vector2f(8.f, 16.f));
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
			this->playerView->setCenter(sf::Vector2f(std::floor(this->playerPos.x), 696.f) + sf::Vector2f(8.f, 16.f));
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
		this->playerView->setCenter(sf::Vector2f(std::floor(this->playerPos.x), std::floor(this->playerPos.y)) + sf::Vector2f(8.f, 16.f));
	}

}

void GameInstance::updateInput(const float & dt)
{
	//Updating Players Hitbox
	this->topRightCord = this->player->getTopRightCord();
	this->topLeftCord = this->player->getTopLeftCord();
	this->bottomRightCord = this->player->getBottomRightCord();
	this->bottomLeftCord = this->player->getBottomLeftCord();

	//(Debug)
	//std::cout << "dialog count now :" << this->dialogCount << "\n";
	//std::cout << "\n" << "top RightCord = " << this->topRightCord.x <<
	//	", " << this->topRightCord.y << "\n";

	//std::cout << "\n" << "top LeftCord = " << this->topLeftCord.x <<
	//	", " << this->topLeftCord.y << "\n";

	//std::cout << "\n" << "bottom RightCord = " << this->bottomRightCord.x <<
	//	", " << this->bottomRightCord.y << "\n";

	//std::cout << "\n" << "bottom LeftCord = " << this->bottomLeftCord.x <<
	//	", " << this->bottomLeftCord.y << "\n";

	//Closing the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Exit"))))
	{
		this->playerView = new sf::View(sf::Vector2f(500.f, 250.f), sf::Vector2f(1000.f, 500.f)); // Default values do better later
		this->window->setView(*this->playerView);
		this->endInstance();

	}

	//Player Input
	///Combat input
	if (this->playerOnCombat)
	{
		if (this->buttons["Run"]->isPressed())
		{
			this->playerOnCombat = false;
			this->playerLevel = 1;
			this->playerAtk = 5.f;
			this->playerDef = 0.f;
			this->playerHP = { 100.f, 100.f };
			this->playerMP = { 30.f, 30.f };
			return;
		}

		if (this->buttons["Attack"]->isPressed())
		{
			this->enemies["Goblin"]->hp.first -= ( ( playerAtk * playerSkills[0].first) - this->enemies["Goblin"]->def);


			if (this->enemies["Goblin"]->checkIfDefeated())
			{
				this->levelUP();
				this->combatCount++;
				this->playerOnCombat = false;
			}
			else
			{
				this->enemyTurn();
				if (this->playerHP.first < 0.f)
				{
					this->playerOnCombat = false;
					this->playerLevel = 1;
					this->playerAtk = 5.f;
					this->playerDef = 0.f;
					this->playerHP = { 100.f, 100.f };
					this->playerMP = { 30.f, 30.f };

				}
				return;
			}
			
		}

		if ( (this->buttons["Skill_1"]->isPressed()) && (this->playerMP.first > this->playerSkills[1].second) )
		{
			this->playerMP.first -= this->playerSkills[1].second;
			this->enemies["Goblin"]->hp.first -= ( (this->playerAtk * this->playerSkills[1].first) - this->enemies["Goblin"]->def);


			if (this->enemies["Goblin"]->checkIfDefeated())
			{
				this->levelUP();
				this->combatCount++;
				this->playerOnCombat = false;
			}
			else
			{
				this->enemyTurn();

				if (this->playerHP.first < 0.f)
				{
					this->playerOnCombat = false;
					this->playerLevel = 1;
					this->playerAtk = 5.f;
					this->playerDef = 0.f;
					this->playerHP = { 100.f, 100.f };
					this->playerMP = { 30.f, 30.f };

				}
				return;
			}
		}

		if ((this->buttons["Skill_2"]->isPressed()) && (this->playerMP.first > this->playerSkills[2].second))
		{
			this->playerMP.first -= this->playerSkills[2].second;
			this->enemies["Goblin"]->hp.first -= ( (this->playerAtk * this->playerSkills[2].first) - this->enemies["Goblin"]->def );

			if (this->enemies["Goblin"]->checkIfDefeated())
			{
				this->levelUP();
				this->combatCount++;
				this->playerOnCombat = false;
			}
			else
			{
				this->enemyTurn();
				if (this->playerHP.first < 0.f)
				{
					this->playerOnCombat = false;
					this->playerLevel = 1;
					this->playerAtk = 5.f;
					this->playerDef = 0.f;
					this->playerHP = { 100.f, 100.f };
					this->playerMP = { 30.f, 30.f };
						
				}
				return;
			}
		}
	}
	///Movimentation & Interaction
	if (this->playerOnInteraction == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("START COMBAT"))))
		{

			if (((this->topLeftCord.x >= this->interactiveObjects[0].getPosition().x) &&
				(this->topLeftCord.y >= this->interactiveObjects[0].getPosition().y)) &&
				((this->topLeftCord.x <= this->interactiveObjects[0].getPosition().x + this->interactiveObjects[1].getSize().x) &&
				(this->topLeftCord.y <= this->interactiveObjects[0].getPosition().y) + this->interactiveObjects[1].getSize().y))
			{
				this->initializeCombat();
			}
			else
				if (((this->topRightCord.x >= this->interactiveObjects[0].getPosition().x) &&
					(this->topRightCord.y >= this->interactiveObjects[0].getPosition().y)) &&
					((this->topRightCord.x <= this->interactiveObjects[0].getPosition().x + this->interactiveObjects[0].getSize().x) &&
					(this->topRightCord.y <= this->interactiveObjects[0].getPosition().y) + this->interactiveObjects[0].getSize().y))
				{
					this->initializeCombat();
				}
				else
					if (((this->bottomLeftCord.x >= this->interactiveObjects[0].getPosition().x) &&
						(this->bottomLeftCord.y >= this->interactiveObjects[0].getPosition().y)) &&
						((this->bottomLeftCord.x <= this->interactiveObjects[0].getPosition().x + this->interactiveObjects[0].getSize().x) &&
						(this->bottomLeftCord.y <= this->interactiveObjects[0].getPosition().y) + this->interactiveObjects[0].getSize().y))
					{
						this->initializeCombat();

					}
					else
						if (((this->bottomRightCord.x >= this->interactiveObjects[0].getPosition().x) &&
							(this->bottomRightCord.y >= this->interactiveObjects[0].getPosition().y)) &&
							((this->bottomRightCord.x <= this->interactiveObjects[0].getPosition().x + this->interactiveObjects[0].getSize().x) &&
							(this->bottomRightCord.y <= this->interactiveObjects[0].getPosition().y) + this->interactiveObjects[0].getSize().y))
						{
							this->initializeCombat();
						}
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACT"))))
		{
			for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumInteractObj(); i++)
			{
				if (((this->topLeftCord.x >= this->interactiveObjects[i].getPosition().x) &&
					(this->topLeftCord.y >= this->interactiveObjects[i].getPosition().y)) &&
					((this->topLeftCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
					(this->topLeftCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
				{
					this->initializeInteraction(i);
				}
				else
					if (((this->topRightCord.x >= this->interactiveObjects[i].getPosition().x) &&
						(this->topRightCord.y >= this->interactiveObjects[i].getPosition().y)) &&
						((this->topRightCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
						(this->topRightCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
					{
						this->initializeInteraction(i);
					}
					else
						if (((this->bottomLeftCord.x >= this->interactiveObjects[i].getPosition().x) &&
							(this->bottomLeftCord.y >= this->interactiveObjects[i].getPosition().y)) &&
							((this->bottomLeftCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
							(this->bottomLeftCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
						{
							this->initializeInteraction(i);

						}
						else
							if (((this->bottomRightCord.x >= this->interactiveObjects[i].getPosition().x) &&
								(this->bottomRightCord.y >= this->interactiveObjects[i].getPosition().y)) &&
								((this->bottomRightCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
								(this->bottomRightCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
							{

								this->initializeInteraction(i);

							}
			}

			for (short int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumNPC(); i++)
			{
				if (((this->topLeftCord.x >= this->npc[i].getPosition().x) &&
					(this->topLeftCord.y >= this->npc[i].getPosition().y)) &&
					((this->topLeftCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
					(this->topLeftCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
				{
					this->initializeDialog(i);
				}
				else
					if (((this->topRightCord.x >= this->npc[i].getPosition().x) &&
						(this->topRightCord.y >= this->npc[i].getPosition().y)) &&
						((this->topRightCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
						(this->topRightCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
					{

						this->initializeDialog(i);
					}
					else
						if (((this->bottomLeftCord.x >= this->npc[i].getPosition().x) &&
							(this->bottomLeftCord.y >= this->npc[i].getPosition().y)) &&
							((this->bottomLeftCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
							(this->bottomLeftCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
						{
							this->initializeDialog(i);
						}
						else
							if (((this->bottomRightCord.x >= this->npc[i].getPosition().x) &&
								(this->bottomRightCord.y >= this->npc[i].getPosition().y)) &&
								((this->bottomRightCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
								(this->bottomRightCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
							{
								this->initializeDialog(i);
							}
			}
		}

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
						//(Debug)
						//std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
						//	" ," << this->objects[i].getPosition().y << " I Stoped the movement";

						this->player->FinishMovement();
						return;
					}
				}
			}
			this->player->move(-1.f, 0.f, dt);
		}
		else
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE RIGHT")))) ||
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
							//(debug)
							//std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
							//	" ," << this->objects[i].getPosition().y << " I Stoped the movement";
							this->player->FinishMovement();
							return;
						}
					}
				}
				this->player->move(1.f, 0.f, dt);
			}
			else
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE UP")))) ||
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
								//(debug)
								//std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
								//	" ," << this->objects[i].getPosition().y << " I Stoped the movement";

								this->player->FinishMovement();
								return;
							}
						}
					}
					this->player->move(0.f, -1.f, dt);
				}
				else
					if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE DOWN")))) ||
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
									//(debug)
									//std::cout << "\n\n" << "OBJ " << i << " POSITION = " << this->objects[i].getPosition().x <<
									//	" ," << this->objects[i].getPosition().y << " I Stoped the movement";

									this->player->FinishMovement();
									return;
								}
							}
						}
						this->player->move(0.f, 1.f, dt);
					}
	}
	else
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACT")))) && (!interactionDelay))
		{

			for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumInteractObj(); i++)
			{
				if (((this->topLeftCord.x >= this->interactiveObjects[i].getPosition().x) &&
					(this->topLeftCord.y >= this->interactiveObjects[i].getPosition().y)) &&
					((this->topLeftCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
					(this->topLeftCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
				{
					if (this->dialogCount < this->InteractionsSize[i])
					{
						this->initializeInteraction(i);
						return;
					}
					else
					{
						this->dialogCount = 0;
						this->playerOnInteraction = false;
						return;

					}
				}
				else
					if (((this->topRightCord.x >= this->interactiveObjects[i].getPosition().x) &&
						(this->topRightCord.y >= this->interactiveObjects[i].getPosition().y)) &&
						((this->topRightCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
						(this->topRightCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
					{
						if (this->dialogCount < this->InteractionsSize[i])
						{
							this->initializeInteraction(i);
							return;
						}
						else
						{
							this->dialogCount = 0;
							this->playerOnInteraction = false;
							return;
						}
					}
					else
						if (((this->bottomLeftCord.x >= this->interactiveObjects[i].getPosition().x) &&
							(this->bottomLeftCord.y >= this->interactiveObjects[i].getPosition().y)) &&
							((this->bottomLeftCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
							(this->bottomLeftCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
						{
							if (this->dialogCount < this->InteractionsSize[i])
							{
								this->initializeInteraction(i);
								return;
							}
							else
							{
								this->dialogCount = 0;
								this->playerOnInteraction = false;
								return;
							}
						}
						else
							if (((this->bottomRightCord.x >= this->interactiveObjects[i].getPosition().x) &&
								(this->bottomRightCord.y >= this->interactiveObjects[i].getPosition().y)) &&
								((this->bottomRightCord.x <= this->interactiveObjects[i].getPosition().x + this->interactiveObjects[i].getSize().x) &&
								(this->bottomRightCord.y <= this->interactiveObjects[i].getPosition().y) + this->interactiveObjects[i].getSize().y))
							{
								if (this->dialogCount < this->InteractionsSize[i])
								{
									this->initializeInteraction(i);
									return;
								}
								else
								{
									this->dialogCount = 0;
									this->playerOnInteraction = false;
									return;
								}
							}
			}

			for (int i = 0; i < this->scenario["CENTRAL_MAP"]->getNumNPC(); i++)
			{
				if (((this->topLeftCord.x >= this->npc[i].getPosition().x) &&
					(this->topLeftCord.y >= this->npc[i].getPosition().y)) &&
					((this->topLeftCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
					(this->topLeftCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
				{
					if (this->dialogCount < this->dialogSize[i])
					{
						this->initializeDialog(i);
						return;
					}
					else
					{
						this->dialogCount = 0;
						this->playerOnInteraction = false;
						return;
					}
				}
				else
					if (((this->topRightCord.x >= this->npc[i].getPosition().x) &&
						(this->topRightCord.y >= this->npc[i].getPosition().y)) &&
						((this->topRightCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
						(this->topRightCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
					{
						if (this->dialogCount < this->dialogSize[i])
						{
							this->initializeDialog(i);
							return;
						}
						else
						{
							this->dialogCount = 0;
							this->playerOnInteraction = false;
							return;
						}
					}
					else
						if (((this->bottomLeftCord.x >= this->npc[i].getPosition().x) &&
							(this->bottomLeftCord.y >= this->npc[i].getPosition().y)) &&
							((this->bottomLeftCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
							(this->bottomLeftCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
						{
							if (this->dialogCount < this->dialogSize[i])
							{
								this->initializeDialog(i);
								return;
							}
							else
							{
								this->dialogCount = 0;
								this->playerOnInteraction = false;
								return;
							}
						}
						else
							if (((this->bottomRightCord.x >= this->npc[i].getPosition().x) &&
								(this->bottomRightCord.y >= this->npc[i].getPosition().y)) &&
								((this->bottomRightCord.x <= this->npc[i].getPosition().x + this->npc[i].getSize().x) &&
								(this->bottomRightCord.y <= this->npc[i].getPosition().y) + this->npc[i].getSize().y))
							{
								if (this->dialogCount < this->dialogSize[i])
								{
									this->initializeDialog(i);
									return;
								}
								else
								{
									this->dialogCount = 0;
									this->playerOnInteraction = false;
									return;
								}
							}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		{
			this->dialogCount = 0;
			this->playerOnInteraction = false;
		}
	}
}

bool GameInstance::updateInputDelay(const float & dt)
{
	if (this->interactionTimer > 0.f)
	{
		this->interactionTimer -= dt;
		return true;
	}
	this->interactionTimer = 2 * dt;
	return false;
}

void GameInstance::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePositionView);
	}

}

void GameInstance::update(const float& dt)
{
	
	this->updateMousePositions(); // TO DO (playerview_
	this->updateButtons();
	this->interactionDelay = this->updateInputDelay(dt);
	this->updateInput(dt);
	this->player->update(dt);
	this->scenario["CENTRAL_MAP"]->updateCollision(this->player);
	this->updateView(dt);

}

void GameInstance::renderButtons(sf::RenderTarget * target , std::string key)
{

	this->buttons.at(key)->render(*target);

	if (this->playerOnCombat)
	{

		if (this->buttons["Attack"]->isHovered())
		{
			sf::Text info;
			info.setPosition(sf::Vector2f(this->buttons["Attack"]->getPosition().x - 40.f,
											this->buttons["Attack"]->getPosition().y + 25.f));
			info.setCharacterSize(9);
			info.setFont(this->font1);
			std::stringstream ss;
			ss << std::setprecision(4) << "Damage Multiplier : " << this->playerSkills[0].first
				<< " - > MP Cost : " << this->playerSkills[0].first;
			info.setString(ss.str());
			target->draw(info);
		}
		else
			if (this->buttons["Skill_1"]->isHovered())
			{
				sf::Text info;
				info.setPosition(sf::Vector2f(this->buttons["Skill_1"]->getPosition().x - 40.f,
												this->buttons["Skill_1"]->getPosition().y + 25.f));
				info.setCharacterSize(9);
				info.setFont(this->font1);
				std::stringstream ss;
				ss << std::setprecision(4) << "Damage Multiplier : " << this->playerSkills[1].first
					<< " - > MP Cost : " << this->playerSkills[1].first;
				info.setString(ss.str());
				target->draw(info);
			}
			else
				if (this->buttons["Skill_2"]->isHovered())
				{
					sf::Text info;
					info.setPosition(sf::Vector2f(this->buttons["Skill_2"]->getPosition().x - 40.f,
													this->buttons["Skill_2"]->getPosition().y + 25.f));
					info.setCharacterSize(9);
					info.setFont(this->font1);
					std::stringstream ss;
					ss << std::setprecision(4) << "Damage Multiplier : " << this->playerSkills[2].first
						<< " - > MP Cost : " << this->playerSkills[2].first;
					info.setString(ss.str());
					target->draw(info);
				}
				else
					if (this->buttons["Run"]->isHovered())
					{
						sf::Text info;
						info.setPosition(sf::Vector2f(this->buttons["Skill_2"]->getPosition().x - 80.f,
														this->buttons["Skill_2"]->getPosition().y + 25.f));
						info.setCharacterSize(9);
						info.setFont(this->font1);
						std::stringstream ss;
						ss << " End the combat ";
						info.setString(ss.str());
						target->draw(info);
					}
	}
}

void GameInstance::renderDisplayCombat(sf::RenderTarget * target, std::string key)
{
	sf::Text playerInfo;
	playerInfo.setPosition(sf::Vector2f(this->combatDisplay.getPosition().x + 5.f,
		this->combatDisplay.getPosition().y + 5.f));
	playerInfo.setCharacterSize(12);
	playerInfo.setFont(this->font1);
	std::stringstream ss;
	ss << std::setprecision(4)
		<< "You" << "(" << this->playerLevel << ")" << "\n"
		<< "HP : " << this->playerHP.first << "/" << this->playerHP.second << "\n"
		<< "MP : " << this->playerMP.first << "/" << this->playerMP.second;
	playerInfo.setString(ss.str());
	target->draw(playerInfo);

	sf::Text enemyInfo;
	enemyInfo.setPosition(sf::Vector2f(this->combatDisplay.getPosition().x + 80.f,
		this->combatDisplay.getPosition().y + 5.f));
	enemyInfo.setCharacterSize(12);
	enemyInfo.setFont(this->font1);
	std::stringstream ss2;
	ss2 << std::setprecision(4)
		<< key << "(" << this->enemies[key]->level << ")" << "\n"
		<< "HP : " << this->enemies[key]->hp.first << "/" << this->enemies[key]->hp.second << "\n"
		<< "MP : " << this->enemies[key]->mp.first << "/" << this->enemies[key]->mp.second;
	enemyInfo.setString(ss2.str());
	target->draw(enemyInfo);
}

void GameInstance::render(sf::RenderTarget* target)
{
	if (!target) // if target is nullpr
	{
		target = this->window;
	}

	this->scenario["CENTRAL_MAP"]->render(target);
	this->player->render(*target);
	this->window->setView(*playerView);
	if (this->playerOnInteraction) {

		this->renderButtons(target, this->atualDialog);
	}
	if (this->playerOnCombat)
	{
		target->draw(this->combatDisplay);
		target->draw(this->actionsMenu);

		this->renderDisplayCombat(target, "Goblin");
		this->renderButtons(target, "Attack");
		this->renderButtons(target, "Skill_1");
		this->renderButtons(target, "Skill_2");
		this->renderButtons(target, "Run");

	}

}